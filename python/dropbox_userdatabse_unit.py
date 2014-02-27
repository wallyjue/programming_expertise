#!/usr/bin/python
import sys
sys.dont_write_bytecode = True
import unittest
import sqlite as sqlite
import dropbo_db2 as db
import datetime
import os

class UnitTest_dropbox_userdatabase(unittest.TestCase):
  def setUp(self):
    # self.path = '/tmp/test_db.db'
    self.path = ":memory:"
    self.db = sqlite.Connection(self.path)
    
  def tearDown(self):
    self.db.close()
    # os.unlink(self.path)


if __name__ == '__main__':
  unittest.main()
