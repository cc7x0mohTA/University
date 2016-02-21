package com.januszsoft.kebabexplorer.anzen.datasource

import com.mongodb.BasicDBObject
import com.mongodb.DBCollection
import com.mongodb.DBObject
import com.mongodb.util.JSON
import org.springframework.beans.factory.annotation.Autowired
import org.springframework.beans.factory.annotation.Qualifier
import org.springframework.stereotype.Component

@Component
class RestaurantDataSource {

  @Autowired
  @Qualifier("restaurantCollection")
  DBCollection restaurants

// Get:

  def getRestaurantInfo(String restaurantName) {
    def query = (BasicDBObject) ["name": (restaurantName)]
    def restaurantInfo = restaurants.findOne(query)
    restaurantInfo?.removeField("_id")
    return restaurantInfo
  }

  def getAllRestaurantsInfo() {
    def allRestaurantsInfo = restaurants.find().toArray()
    allRestaurantsInfo.each { it.removeField("_id") }
    return allRestaurantsInfo
  }

  def getAllRestaurantsInfoWithGeolocation(double longitude, double latitude, int radius) {
    def centre = [ 'type' : 'Point', 'coordinates' : [longitude, latitude] ]
    def query = (BasicDBObject) ['location': [ '$near' : [ '$maxDistance' : (radius), '$geometry' : centre ]]]
    def restaurantInfo = restaurants.find(query).toArray()
    restaurantInfo.each { it.removeField("_id") }
    return restaurantInfo
  }

// Add:

  def addRestaurant(String queryBody) {
    def query = (DBObject) JSON.parse(queryBody)
    restaurants.insert(query)
  }

// Delete:

  def deleteRestaurant(String restaurantName) {
    def query = (BasicDBObject) ["name": (restaurantName)]
    restaurants.remove(query)
  }

// Update:

  def updateRestaurantInfo(String restaurantName, String queryJson) {
    def findQuery = (BasicDBObject) ["name": (restaurantName)]
    def updateQuery = (BasicDBObject) ['$set': JSON.parse(queryJson)]
    restaurants.update(findQuery, updateQuery, true, false)
  }

// Others:

  boolean checkIfRestaurantExist(String restaurantName) {
    def query = (BasicDBObject) ["name": (restaurantName)]
    return restaurants.findOne(query) != null
  }

}
