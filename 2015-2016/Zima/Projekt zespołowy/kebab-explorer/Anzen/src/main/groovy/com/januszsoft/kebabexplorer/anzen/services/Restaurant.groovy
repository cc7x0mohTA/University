package com.januszsoft.kebabexplorer.anzen.services

import com.januszsoft.kebabexplorer.anzen.datasource.RestaurantDataSource
import com.januszsoft.kebabexplorer.anzen.utils.ServiceResponses
import com.januszsoft.kebabexplorer.anzen.utils.ServiceUtils
import org.springframework.beans.factory.annotation.Autowired
import org.springframework.stereotype.Component

import javax.ws.rs.*
import javax.ws.rs.core.MediaType
import javax.ws.rs.core.Response

@Component
@Path("/restaurant")
@Produces(MediaType.APPLICATION_JSON)
public class Restaurant {

  @Autowired
  RestaurantDataSource dataSource

  @GET
  @Path("/{restaurantName}")
  public Response getRestaurantInfo(@PathParam("restaurantName") String restaurantName) {

    if (!dataSource.checkIfRestaurantExist(restaurantName)) {
      return ServiceResponses.GIVEN_RESTAURANT_DOESNT_EXIST_RESPONSE()
    }

    def restaurantInfo = dataSource.getRestaurantInfo(restaurantName)
    return ServiceResponses.OK_RESPONSE_WITH_BODY(restaurantInfo.toString())
  }

  @GET
  @Path("/")
  public Response getAllRestaurantsInfo(@QueryParam("longitude") String longitude,
                                        @QueryParam("latitude") String latitude,
                                        @QueryParam("radius") String radius) {

    if (ServiceUtils.checkIfArgumentsAreBlank(longitude, latitude, radius)) {
      def allRestaurantsInfo = dataSource.getAllRestaurantsInfo()
      return ServiceResponses.OK_RESPONSE_WITH_BODY(allRestaurantsInfo)
    }

    def allRestaurantsInfo = dataSource.getAllRestaurantsInfoWithGeolocation(
      Double.parseDouble(longitude), Double.parseDouble(latitude), Integer.parseInt(radius))

    return ServiceResponses.OK_RESPONSE_WITH_BODY(allRestaurantsInfo)
  }

  @POST
  @Path("/{restaurantName}")
  @Consumes(MediaType.APPLICATION_JSON)
  public Response addRestaurant(@PathParam("restaurantName") String restaurantName, String queryBody) {

    if (ServiceUtils.checkIfArgumentsAreBlank(restaurantName, queryBody)) {
      return ServiceResponses.BLANK_ARGUMENTS_RESPONSE()
    }

    if (dataSource.checkIfRestaurantExist(restaurantName)) {
      return ServiceResponses.GIVEN_RESTAURANT_EXIST_RESPONSE()
    }

    if (!ServiceUtils.validateJson(ServiceUtils.RESTAURANT_ADD_SCHEMA, queryBody)) {
      return ServiceResponses.ILLEGAL_JSON_RESPONSE()
    }

    dataSource.addRestaurant(queryBody)
    return ServiceResponses.OK()
  }

  @DELETE
  @Path("/{restaurantName}")
  public Response deleteRestaurant(@PathParam("restaurantName") String restaurantName) {

    if (ServiceUtils.checkIfArgumentsAreBlank(restaurantName)) {
      return ServiceResponses.BLANK_ARGUMENTS_RESPONSE()
    }

    if (!dataSource.checkIfRestaurantExist(restaurantName)) {
      return ServiceResponses.GIVEN_RESTAURANT_DOESNT_EXIST_RESPONSE()
    }

    dataSource.deleteRestaurant(restaurantName)
    return ServiceResponses.OK()
  }

  @PUT
  @Path("/{restaurantName}")
  @Consumes(MediaType.APPLICATION_JSON)
  public Response changeRestaurantBasicData(@PathParam("restaurantName") String restaurantName, String queryBody) {

    if (ServiceUtils.checkIfArgumentsAreBlank(restaurantName, queryBody)) {
      return ServiceResponses.BLANK_ARGUMENTS_RESPONSE()
    }

    if (!dataSource.checkIfRestaurantExist(restaurantName)) {
      return ServiceResponses.GIVEN_RESTAURANT_DOESNT_EXIST_RESPONSE()
    }

    if (!ServiceUtils.validateJson(ServiceUtils.RESTAURANT_UPDATE_SCHEMA, queryBody)) {
      return ServiceResponses.ILLEGAL_JSON_RESPONSE()
    }

    dataSource.updateRestaurantInfo(restaurantName, queryBody)
    return ServiceResponses.OK()
  }

}