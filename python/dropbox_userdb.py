#!/usr/bin/python
import sqlite3 as lite
import sys
from optparse import OptionParser
import os


usage_ = "usage: %prog [options] arg"
table_name = 'dropbox_user'
column_local_user_name = 'local_username'
column_dropbox_account = 'dropbox_account'
column_dropbox_nickname = 'dropbox_nickname'
column_lansync = 'lansync'
column_autostart = 'autostart'
column_exclude_list = 'exclude_list'
column_pid = 'pid'
column_home = 'home'


def listalluser():
  str = os.popen("/sbin/user_cmd -u").read()
  a = str.split("\n")
  for b in a:
    print b
  

def usage():
  print usage_

def create():
  try:
    con = lite.connect('/etc/config/dropbox_user.db')
    
    cur = con.cursor()    
    cur.execute('''create table '''+table_name+''' ('''+ column_local_user_name+ 
    ''' TEXT PRIMARY KEY, ''' +column_dropbox_account+''' TEXT not null, ''' +column_dropbox_nickname+
    ''' TEXT not null, ''' +column_lansync+''' BOOL not null, ''' +column_autostart+
    ''' BOOL not null, ''' +column_exclude_list+''' TEXT not null, ''' +column_pid+
    ''' INT not null, ''' +column_home+''' TEXT not null);''')          
    
  except lite.Error, e:
    #print "Error %s" % e.args[0]
    print "ret=0"
    return
  
  print "ret=1"
    

def disable(argv):
  queryuser = dict()
  ret = argv.split('&')
  for item in ret:
    ret2 = item.split('=')
    queryuser.update({ret2[0] : ret2[1]})
  try:
    con = lite.connect('/etc/config/dropbox_user.db')
    
    cur = con.cursor()
    cur.execute('''delete from '''+table_name+''' where '''+
      column_local_user_name+''' == '%s' ''' % (queryuser[column_local_user_name],))
          
    con.commit()
  except lite.Error, e:
    #print "Error %s" % e.args[0]
    print "ret=0"
    return
  
  print "ret=1"
  
  
def enable(argv):
  queryuser = dict()
  ret = argv.split('&')
  for item in ret:
    ret2 = item.split('=')
    queryuser.update({ret2[0] : ret2[1]})
    #print ret2
    
  try:
    con = lite.connect('/etc/config/dropbox_user.db')
    
    cur = con.cursor()
    
    cur.execute("insert or replace into "+table_name+" values(\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\')" 
      % (queryuser[column_local_user_name],queryuser[column_dropbox_account],queryuser[column_dropbox_nickname],
      queryuser[column_lansync],queryuser[column_autostart],queryuser[column_exclude_list],queryuser[column_pid],queryuser[column_home]))
    #print '''insert into "+table_name+" values(\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\')''' 
        #% (queryuser[column_local_user_name],queryuser[column_dropbox_account],queryuser[column_dropbox_nickname],queryuser[column_lansync],queryuser[column_autostart],queryuser[column_exclude_list],queryuser[column_pid],queryuser[column_home])
    con.commit()   
    
  except lite.Error, e:
    print "ret=0"
    #print "Error %s" % e.args[0]
    return
  
  print "ret=1"
  
def update(argv):
  queryuser = dict()
  ret = argv.split('&')
  for item in ret:
    ret2 = item.split('=')
    queryuser.update({ret2[0] : ret2[1]})
  try:
    con = lite.connect('/etc/config/dropbox_user.db')
    
    cur = con.cursor()  
    cur.execute("replace into "+table_name+" values(\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\')" % 
      (queryuser[column_local_user_name],queryuser[column_dropbox_account],queryuser[column_dropbox_nickname],
      queryuser[column_lansync],queryuser[column_autostart],queryuser[column_exclude_list],queryuser[column_pid],queryuser[column_home]))
    con.commit()
  except lite.Error, e:
    #print "Error %s" % e.args[0]
    print "ret=0"
    return
    
  print "ret=1"

def queryall():
  try:
    con = lite.connect('/etc/config/dropbox_user.db')
    
    cur = con.cursor()
    cur.execute('''select * from '''+table_name)
    
  except lite.Error, e:
    #print "Error %s" % e.args[0]
    print "ret=0"
    return
    
  #print cur.fetchall()
  for row in cur:
    print row[0]+"&"+row[7]


def query(argv):
  queryuser = dict()
  ret = argv.split('&')
  for item in ret:
    ret2 = item.split('=')
    queryuser.update({ret2[0] : ret2[1]})
    
  try:
    con = lite.connect('/etc/config/dropbox_user.db')
    cur = con.cursor()
    cur.execute('''select * from '''+table_name+''' where '''+
      column_local_user_name+''' = '%s' ''' % (queryuser[column_local_user_name],))
          
    con.commit()
  except KeyError, e:
    print "key error %s" % e.args[0]
  except lite.Error, e:
    print "Error %s" % e.args[0]
    print "ret=0"
    return
    
  if cur.rowcount < 1:
    print "ret=0"
    return
  
  print cur.fetchall()
  


def main(argv):
  print argv
  if( len(argv) <= 1):
    usage()
    return
    
  
  parser = OptionParser()
  parser.add_option("-c", "--create", action="store_true", dest="create")
  parser.add_option("-a", "--queryall", action="store_true", dest="queryall")
  parser.add_option("-q", "--query", dest="query")
  parser.add_option("-u", "--update", dest="update")
  parser.add_option("-e", "--enable", dest="enable")
  parser.add_option("-d", "--disable", dest="disable")
  #parser.add_option("-h", "", dest="function", default=True)
  (options, args) = parser.parse_args()
  #print len(args)
  #if len(args) != 1:
    #parser.error("in correct number of arguments");
  if options.create:
    create()
    return
  elif options.query:
    #print "query string:%s" % options.query
    query(options.query)
    return
  elif options.queryall:
    #print "query string:%s" % options.queryall
    queryall()
    return
  elif options.update:
    #print "update string:%s" % options.update
    update(options.update)
    return
  elif options.enable:
    # insert entry if not exist
    #print "enable string:%s" % options.enable
    enable( options.enable)   
    return
  elif options.disable:
    # delete entry
    #print "disable string:%s" % options.disable
    disable( options.disable)   
    return   
  else:
    usage()

class DropboxUserDatabase:
  '''a wrapper class for dropbox user management'''
  
  def __init__(self, argv):
    self.argv = argv
    
  
  def usage():
    print usage_

  def create():
    try:
      con = lite.connect('dropbox_user.db')
      
      cur = con.cursor()    
      cur.execute('''create table '''+table_name+''' ('''+ column_local_user_name+ 
      ''' TEXT PRIMARY KEY, ''' +column_dropbox_account+''' TEXT not null, ''' +column_dropbox_nickname+
      ''' TEXT not null, ''' +column_lansync+''' BOOL not null, ''' +column_autostart+
      ''' BOOL not null, ''' +column_exclude_list+''' TEXT not null, ''' +column_pid+
      ''' INT not null, ''' +column_home+''' TEXT not null);''')          
      
    except lite.Error, e:
      #print "Error %s" % e.args[0]
      print "ret=0"
      return
    
    print "ret=1"
      

  def disable(argv):
    queryuser = dict()
    ret = argv.split('&')
    for item in ret:
      ret2 = item.split('=')
      queryuser.update({ret2[0] : ret2[1]})
    try:
      con = lite.connect('dropbox_user.db')
      
      cur = con.cursor()
      cur.execute('''delete from '''+table_name+''' where '''+
        column_local_user_name+''' == '%s' ''' % (queryuser[column_local_user_name],))
            
      con.commit()
    except lite.Error, e:
      #print "Error %s" % e.args[0]
      print "ret=0"
      return
    
    print "ret=1"
    
    
  def enable(argv):
    queryuser = dict()
    ret = argv.split('&')
    for item in ret:
      ret2 = item.split('=')
      queryuser.update({ret2[0] : ret2[1]})
      #print ret2
      
    try:
      con = lite.connect('dropbox_user.db')
      
      cur = con.cursor()
      
      cur.execute("insert or replace into "+table_name+" values(\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\')" 
        % (queryuser[column_local_user_name],queryuser[column_dropbox_account],queryuser[column_dropbox_nickname],
        queryuser[column_lansync],queryuser[column_autostart],queryuser[column_exclude_list],queryuser[column_pid],queryuser[column_home]))
      #print '''insert into "+table_name+" values(\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\')''' 
          #% (queryuser[column_local_user_name],queryuser[column_dropbox_account],queryuser[column_dropbox_nickname],queryuser[column_lansync],queryuser[column_autostart],queryuser[column_exclude_list],queryuser[column_pid],queryuser[column_home])
      con.commit()   
      
    except lite.Error, e:
      print "ret=0"
      #print "Error %s" % e.args[0]
      return
    
    print "ret=1"
    
  def update(argv):
    queryuser = dict()
    ret = argv.split('&')
    for item in ret:
      ret2 = item.split('=')
      queryuser.update({ret2[0] : ret2[1]})
    try:
      con = lite.connect('dropbox_user.db')
      
      cur = con.cursor()  
      cur.execute("replace into "+table_name+" values(\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\')" % 
        (queryuser[column_local_user_name],queryuser[column_dropbox_account],queryuser[column_dropbox_nickname],
        queryuser[column_lansync],queryuser[column_autostart],queryuser[column_exclude_list],queryuser[column_pid],queryuser[column_home]))
      con.commit()
    except lite.Error, e:
      #print "Error %s" % e.args[0]
      print "ret=0"
      return
      
    print "ret=1"

  def queryall():
    try:
      con = lite.connect('dropbox_user.db')
      
      cur = con.cursor()
      cur.execute('''select * from '''+table_name)
      
    except lite.Error, e:
      #print "Error %s" % e.args[0]
      print "ret=0"
      return
      
    #print cur.fetchall()
    for row in cur:
      print row[0]+"&"+row[7]


  def query(argv):
    queryuser = dict()
    ret = argv.split('&')
    for item in ret:
      ret2 = item.split('=')
      queryuser.update({ret2[0] : ret2[1]})
      
    try:
      con = lite.connect('dropbox_user.db')
      cur = con.cursor()
      cur.execute('''select * from '''+table_name+''' where '''+
        column_local_user_name+''' = '%s' ''' % (queryuser[column_local_user_name],))
            
      con.commit()
    except KeyError, e:
      print "key error %s" % e.args[0]
    except lite.Error, e:
      print "Error %s" % e.args[0]
      print "ret=0"
      return
      
    if cur.rowcount < 1:
      print "ret=0"
      return
    
    print cur.fetchall()  
  


if __name__ == "__main__":
#db = DropboxUserDatabase( sys.argv)
  main(sys.argv)
