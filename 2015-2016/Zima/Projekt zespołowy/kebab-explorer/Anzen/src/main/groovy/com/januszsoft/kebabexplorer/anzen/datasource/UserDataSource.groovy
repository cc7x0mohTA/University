package com.januszsoft.kebabexplorer.anzen.datasource

import com.mongodb.BasicDBObject
import com.mongodb.DBCollection
import com.mongodb.DBObject
import com.mongodb.util.JSON
import org.springframework.beans.factory.annotation.Autowired
import org.springframework.beans.factory.annotation.Qualifier
import org.springframework.stereotype.Component

@Component
class UserDataSource {

  @Autowired
  @Qualifier("userCollection")
  DBCollection users

// Get:

  def getUserInfo(String userLogin) {
    def query = (BasicDBObject) ["login": (userLogin)]
    def userInfo = users.findOne(query)
    userInfo?.removeField("_id")
    userInfo?.removeField("password_hash")
    return userInfo
  }

  def getAllUsersInfo() {
    def allUsersInfo = users.find().toArray()
    allUsersInfo.each { it.removeField("_id") && it.removeField("password_hash") }
    return allUsersInfo
  }

// Add:

  def addUser(String queryBody) {
    def query = (DBObject) JSON.parse(queryBody)
    query.put("password_hash", query.get("password_hash")) // TODO Generating Password Hash
    users.insert(query)
  }

// Delete:

  def deleteUser(String userLogin) {
    def query = (BasicDBObject) ["login": (userLogin)]
    users.remove(query)
  }

// Update:

  def updateUserInfo(String userLogin, String queryJson) {
    def findQuery = (BasicDBObject) ["login": (userLogin)]
    def updateQuery = (BasicDBObject) ['$set': JSON.parse(queryJson)]
    users.update(findQuery, updateQuery, true, false)
  }

// Others:

  boolean checkIfUserExist(String userLogin) {
    def query = (BasicDBObject) ["login": (userLogin)]
    return users.findOne(query) != null
  }

  String getPasswordHash(String userLogin) {
    def query = (BasicDBObject) ["login": (userLogin)]
    def userInfo = users.findOne(query)
    return userInfo["password_hash"]
  }

}
