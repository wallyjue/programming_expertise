#!/usr/bin/python
import sys
import sqlite3 as lite
from optparse import OptionParser

usage_ = "usage: %prog [options] arg"

database_name = 'database_for_test.db'
table_name = 'dropbox_user'
column_local_user_name = 'local_username'
column_dropbox_account = 'dropbox_account'
column_dropbox_nickname = 'dropbox_nickname'
column_lansync = 'lansync'
column_autostart = 'autostart'
column_exclude_list = 'exclude_list'
column_pid = 'pid'
column_home = 'home'
column_old_name ='oldname'
column_new_name ='newname'

str_status_code ='''status_code'''

help_str_query_all = '''query all enabled user'''
help_str_query = ''''query data of a specified user, 
                ARGUMENT=\'local_username=[local_username]\''''

help_str_enable = '''enable dropbox capability for a NAS user, 
ARGUMENT=\'local_username=[local_username]&dropbox_account=
[dropbox_account]&dropbox_nickname=[dropbox_nickname]&lansync=
[0/1]&autostart=[0/1]&exclude_list=[file1;file2;file3 ...]&pid=
[pid]&home=[home]\' for lansync and autostart: 1 for true, 0 for false'''
help_str_disable = '''disable dropbox for a NAS user, ARGUMENT=\'
    local_username=[local_username]\''''
    
help_str_update = '''update data of an existing user. data will be remained 
unchanged if ARGUMENT is not given, ARGUMENT=\'
local_username=[local_username]&dropbox_account=
[dropbox_account]&dropbox_nickname=[dropbox_nickname]
&lansync=[0/1]&autostart=[0/1]&exclude_list=[file1;file2
...]&pid=[pid]&home=[home]\'
for lansync and autostart: 1 for true, 0 for false'''

help_str_change='''change local username from old_name to new_name. 
ARGUMENT=\'old_name=[old_name]&new_name=[new_name]\''''

sql_string_create_table = '''create table %s (%s text primary key, 
                            %s text not null, %s text not null, %s int not null, 
                            %s int not null, %s text not null, %s int not null, 
                            %s text not null)''' \
                            % (table_name, column_local_user_name, 
                               column_dropbox_account, column_dropbox_nickname, 
                               column_lansync, column_autostart, 
                               column_exclude_list, column_pid, column_home)

sql_string_query_table = '''select * from sqlite_master where type='table' 
                            and name=\'%s\' ''' %(table_name)

sql_string_drop_table = '''drop table where name=\'%s\' ''' %(table_name)

sql_string_query_all = '''select * from %s''' % (table_name)

class DropboxUserDatabase:
    
    
    def __init__(self, sysargv):
        self.db_conn = ''
        self.db_cs = ''
        
    
    def usage(self):
        print usage_
    
    def main(self, argv):
        parser = OptionParser()
        parser.add_option("-i", "--init", action="store_true", 
                          dest="create", help="create a dropbox_user table")
        parser.add_option("-a", "--queryall", action="store_true", 
                          dest="queryall", help=help_str_query_all)
        parser.add_option("-q", "--query", dest="query", help=help_str_query, 
                          metavar='\'ARGUMENT\'')
        parser.add_option("-u", "--update", dest="update", help=help_str_update, 
                          metavar='\'ARGUMENT\'')
        
        parser.add_option("-e", "--enable", dest="enable", help=help_str_enable, 
                          metavar='\'ARGUMENT\'')
        parser.add_option("-d", "--disable", dest="disable", help=help_str_disable,
                           metavar='\'ARGUMENT\'')
        parser.add_option("-c", "--change_local_username", dest="change", help=help_str_change,
                           metavar='\'ARGUMENT\'')
        #print "%s" %(argv)
        (options, args) = parser.parse_args()
        if options.create:
            self.create_if_not_exist()
            return
        elif options.query:
            self.query(options.query)
            return
        elif options.queryall:
            self.queryall()
            return
        elif options.update:
            self.update(options.update)
            return
        elif options.enable:
            self.enable( options.enable)   
            return
        elif options.disable:
            self.disable( options.disable)   
            return   
        elif options.change:
            self.change_local_username( options.change)   
            return           
        else:
            self.usage()
            return
        
    #def update_str(self, input_dict):
        #print 'a'
        #if input_dict[column_dropbox_account] == []:
            
        
        
    def split_query_str(self, input_str):
        queryuser = dict()
        ret = input_str.split('&')
        if len(ret) < 1:
            raise Exception("query string format error")
        for item in ret:
            ret2 = item.split('=')
            if len(ret2) < 1:
                raise Exception("query string format error")
            else:
                try:
                    queryuser.update({ret2[0] : ret2[1]})
                except IndexError, index_e:
                    raise Exception("query string format error")
        return queryuser    
        
    def check_if_not_exist( self):    
        try:
            self.db_conn = lite.connect(database_name)
            self.db_cs = self.db_conn.cursor()
            self.db_cs.execute(sql_string_query_table)
            self.db_conn.commit()
            self.db_conn.close()
            if self.db_cs.fetchall() != []:
                return False
            else:
                return True
            
        except lite.Error, e:
            #print "Error create:%s" % e
            print "%s=%d" % (str_status_code, -1)
        
    
    def create_if_not_exist( self):
        try:
            self.db_conn = lite.connect(database_name)
            self.db_cs = self.db_conn.cursor()
            self.db_cs.execute(sql_string_query_table)
            self.db_conn.commit()
            #print sql_string_query_table
            #print self.db_cs.fetchall()
            if self.db_cs.fetchall() != []:
                print "not null"
            self.db_cs.execute(sql_string_create_table)
            self.db_conn.commit()
            self.db_conn.close()
        except lite.Error, e:
            #print "Error create:%s" % e
            print "%s=%d" % (str_status_code, -1)
    
    def update(self, sysargv):
        default = ''
        try:
            ret = self.split_query_str(sysargv)
        except Exception, e:
            #print "split string error:%s" % e
            print str_status_code+'=%d' % -2
            return 
        try:
            self.db_conn = lite.connect(database_name)
            self.db_cs = self.db_conn.cursor()
            for eachrow in ret:
                str_update = "update "+table_name+" set "
                if eachrow != column_local_user_name:
                    if (eachrow == column_pid) | (eachrow == column_lansync) | (eachrow == column_autostart):
                        str_update = str_update+eachrow+"="+ret[eachrow]
                    else:
                        str_update = str_update+eachrow+"=\'"+ret[eachrow]+"\'"
                    str_update = str_update + ' where ' + column_local_user_name+'=\''+ret[column_local_user_name]+'\''
                    #print str_update
                    self.db_cs.execute( str_update )
                    self.db_conn.commit()
            
            
            self.db_conn.close()
            print "%s=%d" % (str_status_code, 0)    
        except lite.Error, e:
            #print "Error@update:%s" % e
            print "%s=%d" % (str_status_code, -1)    
            
    def enable(self, sysargv):
        default = ''
        try:
            ret = self.split_query_str(sysargv)
        except Exception, e:
            #print "split string error:%s" % e
            print str_status_code+'=%d' % -2
            return
        try:
            self.db_conn = lite.connect(database_name)
            self.db_cs = self.db_conn.cursor()
            self.db_cs.execute("insert into "+table_name+
                               " values(\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\')" 
                               % (ret.get(column_local_user_name,default), 
                                  ret.get(column_dropbox_account,default),
                                  ret.get(column_dropbox_nickname,default),
                                  ret.get(column_lansync,1),
                                  ret.get(column_autostart,1),
                                  ret.get(column_exclude_list,default),
                                  ret.get(column_pid,default),
                                  ret.get(column_home,default)))                

            self.db_conn.commit()
            self.db_conn.close()
            print "%s=%d" % (str_status_code, 0)
        except lite.Error, e:
            #print "Error@enable:%s" % e
            print "%s=%d" % (str_status_code, -1)
        
        
    def disable(self, sysargv):
        default = ''
        try:
            ret = self.split_query_str(sysargv)
        except Exception, e:
            #print "split string error:%s" % e
            print str_status_code+'=%d' % -2
            return
        try:
            self.db_conn = lite.connect(database_name)
            self.db_cs = self.db_conn.cursor()
                
            self.db_cs.execute("delete from "+table_name+" where %s=\'%s\'" 
                               % (column_local_user_name, 
                                  ret.get(column_local_user_name,default)))
            self.db_conn.commit()
            self.db_conn.close()
            print "%s=%d" % (str_status_code, 0)
        except KeyError, key_error:
            print str_status_code+'=%d' % -2
        except lite.Error, e:
            #print "Error@disable:%s" % e
            print "%s=%d" % (str_status_code, -1)
            
    def change_local_username(self, sysargv):
        default = ''
        try:
            ret = self.split_query_str(sysargv)
        except Exception, e:
            #print "split string error:%s" % e
            print str_status_code+'=%d' % -2
            return
        try:
            if len(ret) != 2:
                print str_status_code+'=%d' % -2
                return 
            #for eachrow in ret:
            self.db_conn = lite.connect(database_name)
            self.db_cs = self.db_conn.cursor()
            sql_ret = self.db_cs.execute('''select * from '''+table_name+''' where '''+
                                         column_local_user_name+'''= \'%s\' ''' % (ret[column_old_name],))
            fetch_ret = sql_ret.fetchone()
            if fetch_ret == None:
                print "%s=%d" % (str_status_code, -3)
                return
            else:
                
                self.db_cs.execute('''delete from '''+table_name+''' where '''+column_local_user_name+'''=\'%s\'''' %(fetch_ret[0]))
                self.db_cs.execute("insert into "+table_name+
                               " values(\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\')" 
                               % (ret[column_new_name], 
                                  fetch_ret[1],
                                  fetch_ret[2],
                                  fetch_ret[3],
                                  fetch_ret[4],
                                  fetch_ret[5],
                                  fetch_ret[6],
                                  fetch_ret[7]))
                self.db_conn.commit()
                self.db_conn.close()
            
            print "%s=%d" % (str_status_code, 0)
        except KeyError, key_error:
            print str_status_code+'=%d' % -2
        except lite.Error, e:
            #print "Error@disable:%s" % e
            print "%s=%d" % (str_status_code, -1)            
            
    def queryall(self):
        try:
            self.db_conn = lite.connect(database_name)
            self.db_cs = self.db_conn.cursor()
            self.db_cs.execute("select count(*) from "+table_name)
            
            rowcount = int( self.db_cs.fetchone()[0] )
            self.db_cs.execute(sql_string_query_all)
            
            strout = "%s=%d&%s=%d" % (str_status_code, 0,'user_list_count',rowcount)
            for eachrow in range(rowcount):
                eachrow = self.db_cs.fetchone()
                strout = strout+'&'+column_local_user_name+'='+eachrow[0]+'&'+column_home+'='+eachrow[7]
                strout = strout +';'
            if rowcount > 0:    
                strout = strout[0:-1]
            print strout
            
            self.db_conn.close()
        except lite.Error, e:
            #print "Error@disable:%s" % e
            print "%s=%d" % (str_status_code, -1)
                
    def query(self, sysargv):
        default = ''
        try:
            ret = self.split_query_str(sysargv)
        except Exception, e:
            #print "split string error:%s" % e
            print "%s=%d" % (str_status_code, -2)
            return
        try:
            self.db_conn = lite.connect(database_name)
            self.db_cs = self.db_conn.cursor()
            #print 'ret:'+ret[column_local_user_name]
            sql_ret = self.db_cs.execute('''select * from '''+table_name+''' where '''+
                                         column_local_user_name+'''= \'%s\' ''' % (ret[column_local_user_name],))
            eachrow = sql_ret.fetchone()
            if eachrow == None:
                print str_status_code+'=%d' % -1
            else:
                strout = str_status_code+'=0&'+column_local_user_name+'='+eachrow[0]+\
                        '&'+column_dropbox_account+'='+eachrow[1]+'&'+\
                        column_dropbox_nickname+'='+eachrow[2]+'&'+\
                        column_lansync+'='+str(eachrow[3])+'&'+\
                        column_autostart+'='+str(eachrow[4])+'&'+\
                        column_exclude_list+'='+eachrow[5]+'&'+\
                        column_pid+'='+str(eachrow[6])+'&'+\
                        column_home+'='+eachrow[7]
                        
                print strout
                
            self.db_conn.commit()
            self.db_conn.close()
        except KeyError, key_error:
            print str_status_code+'=%d' % -2
            #print "KeyError@query:%s" % key_error
        except lite.Error, e:
            #print "Error@query:%s" % e
            print "%s=%d" % (str_status_code, -1)


if __name__ == "__main__":
    db = DropboxUserDatabase(sys.argv)
    db.main(sys.argv)

