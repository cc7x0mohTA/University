package com.januszsoft.kebabexplorer.anzen.datasource

import com.mongodb.BasicDBObject
import com.mongodb.DBCollection
import com.mongodb.DBObject
import com.mongodb.util.JSON
import org.springframework.beans.factory.annotation.Autowired
import org.springframework.beans.factory.annotation.Qualifier
import org.springframework.stereotype.Component

@Component
class CommentDataSource {

  @Autowired
  @Qualifier("commentCollection")
  DBCollection comments

// Get:

  def getCommentInfo(int commentId) {
    def query = (BasicDBObject) ["_id": (commentId)]
    def commentInfo = comments.findOne(query)
    return commentInfo
  }

  def getAllCommentsInfo(String restaurantName, String userName) {

    def findQuery = [:]

    if (restaurantName) {
      findQuery.put("restaurant", restaurantName)
    }

    if (userName) {
      findQuery.put("author", userName)
    }

    findQuery = (BasicDBObject) findQuery
    def allCommentsInfo = comments.find(findQuery).toArray()
    return allCommentsInfo
  }

// Add:

  def addComment(String queryBody) {
    def query = (DBObject) JSON.parse(queryBody)
    query.put("_id", comments.count + 1);
    comments.insert(query)
  }

// Update:

  def updateCommentInfo(int commentId, String queryJson) {
    def findQuery = (BasicDBObject) ["_id": (commentId)]
    def updateQuery = (BasicDBObject) ['$set': JSON.parse(queryJson)]
    comments.update(findQuery, updateQuery, true, false)
  }

// Others:

  boolean checkIfCommentExist(int commentId) {
    def query = (BasicDBObject) ["_id": (commentId)]
    return comments.findOne(query) != null
  }

}