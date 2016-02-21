package com.januszsoft.kebabexplorer.anzen.services

import com.januszsoft.kebabexplorer.anzen.datasource.UserDataSource
import com.januszsoft.kebabexplorer.anzen.utils.ServiceResponses
import com.januszsoft.kebabexplorer.anzen.utils.ServiceUtils
import org.springframework.beans.factory.annotation.Autowired
import org.springframework.stereotype.Component

import javax.ws.rs.*
import javax.ws.rs.core.MediaType
import javax.ws.rs.core.Response

@Component
@Path("/user")
@Produces(MediaType.APPLICATION_JSON)
public class User {

  @Autowired
  UserDataSource dataSource

  @GET
  @Path("/{userLogin}")
  public Response getUserInfo(@PathParam("userLogin") String userLogin) {

    if (!dataSource.checkIfUserExist(userLogin)) {
      return ServiceResponses.GIVEN_USER_DOESNT_EXIST_RESPONSE()
    }

    def userInfo = dataSource.getUserInfo(userLogin)
    return ServiceResponses.OK_RESPONSE_WITH_BODY(userInfo.toString())
  }

  @GET
  @Path("/")
  public Response getAllUsersInfo() {
    def allUsersInfo = dataSource.getAllUsersInfo()
    return ServiceResponses.OK_RESPONSE_WITH_BODY(allUsersInfo)
  }

  @POST
  @Path("/{userLogin}")
  @Consumes(MediaType.APPLICATION_JSON)
  public Response addUser(@PathParam("userLogin") String userLogin, String queryBody) {

    if (ServiceUtils.checkIfArgumentsAreBlank(userLogin, queryBody)) {
      return ServiceResponses.BLANK_ARGUMENTS_RESPONSE()
    }

    if (dataSource.checkIfUserExist(userLogin)) {
      return ServiceResponses.GIVEN_USER_EXIST_RESPONSE()
    }

    if (!ServiceUtils.validateJson(ServiceUtils.USER_ADD_SCHEMA, queryBody)) {
      return ServiceResponses.ILLEGAL_JSON_RESPONSE()
    }

    dataSource.addUser(queryBody)
    return ServiceResponses.OK()
  }

  @DELETE
  @Path("/{userLogin}")
  public Response deleteUser(@PathParam("userLogin") String userLogin) {

    if (ServiceUtils.checkIfArgumentsAreBlank(userLogin)) {
      return ServiceResponses.BLANK_ARGUMENTS_RESPONSE()
    }

    if (!dataSource.checkIfUserExist(userLogin)) {
      return ServiceResponses.GIVEN_RESTAURANT_DOESNT_EXIST_RESPONSE()
    }

    dataSource.deleteUser(userLogin)
    return ServiceResponses.OK()
  }

  @PUT
  @Path("/{userLogin}")
  @Consumes(MediaType.APPLICATION_JSON)
  public Response changeUserBasicData(@PathParam("userLogin") String userLogin, String queryBody) {

    if (ServiceUtils.checkIfArgumentsAreBlank(userLogin, queryBody)) {
      return ServiceResponses.BLANK_ARGUMENTS_RESPONSE()
    }

    if (!dataSource.checkIfUserExist(userLogin)) {
      return ServiceResponses.GIVEN_RESTAURANT_DOESNT_EXIST_RESPONSE()
    }

    if (!ServiceUtils.validateJson(ServiceUtils.USER_UPDATE_SCHEMA, queryBody)) {
      return ServiceResponses.ILLEGAL_JSON_RESPONSE()
    }

    dataSource.updateUserInfo(userLogin, queryBody)
    return ServiceResponses.OK()
  }

}