package com.januszsoft.kebabexplorer.anzen.datasource

import com.mongodb.BasicDBObject
import com.mongodb.DBCollection
import org.springframework.beans.factory.annotation.Autowired
import org.springframework.beans.factory.annotation.Qualifier
import org.springframework.stereotype.Component

import static com.januszsoft.kebabexplorer.anzen.utils.ServiceUtils.generateRandomString
import static com.januszsoft.kebabexplorer.anzen.utils.ServiceUtils.nextDayDate

@Component
class SessionDataSource {

  @Autowired
  @Qualifier("userCollection")
  DBCollection users

  @Autowired
  @Qualifier("sessionCollection")
  DBCollection sessions

  boolean checkIfSessionExist(String cookieHash) {
    def query = (BasicDBObject) ["hash": (cookieHash)]
    return sessions.findOne(query) != null
  }

  def generateAndInsertToken(String userLogin) {
    def hash = generateRandomString(25, 40)
    def token = (BasicDBObject) ["login": (userLogin), "hash": (hash), "expiration_date": (nextDayDate())]
    sessions.insert(token)
    token.removeField("_id")
    return token
  }

  def deleteToken(String tokenHash) {
    def query = (BasicDBObject) ["hash": (tokenHash)]
    sessions.remove(query)
  }

  def getSessionInfo(String cookieHash) {
    def query = (BasicDBObject) ["hash": (cookieHash)]
    def sessionInfo = sessions.findOne(query)
    sessionInfo?.removeField("_id")
    return sessionInfo
  }

}