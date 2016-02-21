package com.januszsoft.kebabexplorer.anzen.services

import com.januszsoft.kebabexplorer.anzen.datasource.CommentDataSource
import com.januszsoft.kebabexplorer.anzen.datasource.RestaurantDataSource
import com.januszsoft.kebabexplorer.anzen.utils.ServiceResponses
import com.januszsoft.kebabexplorer.anzen.utils.ServiceUtils
import org.springframework.beans.factory.annotation.Autowired
import org.springframework.stereotype.Component

import javax.ws.rs.*
import javax.ws.rs.core.MediaType
import javax.ws.rs.core.Response

@Component
@Path("/comment")
@Produces(MediaType.APPLICATION_JSON)
public class Comment {

  @Autowired
  RestaurantDataSource restaurantDataSource

  @Autowired
  CommentDataSource commentDataSource

  @GET
  @Path("/{commentId}")
  public Response getCommentInfo(@PathParam("commentId") int commentId) {

    if (!commentDataSource.checkIfCommentExist(commentId)) {
      return ServiceResponses.GIVEN_COMMENT_DOESNT_EXIST_RESPONSE()
    }

    def commentInfo = commentDataSource.getCommentInfo(commentId)
    return ServiceResponses.OK_RESPONSE_WITH_BODY(commentInfo.toString())
  }

  @GET
  @Path("/")
  public Response getAllCommentsInfo(@QueryParam("restaurantName") String restaurantName,
                                     @QueryParam("userName") String userName) {
    def allCommentsInfo = commentDataSource.getAllCommentsInfo(restaurantName, userName)
    return ServiceResponses.OK_RESPONSE_WITH_BODY(allCommentsInfo)
  }

  @POST
  @Path("/")
  @Consumes(MediaType.APPLICATION_JSON)
  public Response addComment(@QueryParam("restaurantName") String restaurantName, String queryBody) {

    if (ServiceUtils.checkIfArgumentsAreBlank(restaurantName, queryBody)) {
      return ServiceResponses.BLANK_ARGUMENTS_RESPONSE()
    }

    if (!restaurantDataSource.checkIfRestaurantExist(restaurantName)) {
      return ServiceResponses.GIVEN_RESTAURANT_DOESNT_EXIST_RESPONSE()
    }

    if (!ServiceUtils.validateJson(ServiceUtils.COMMENT_ADD_SCHEMA, queryBody)) {
      return ServiceResponses.ILLEGAL_JSON_RESPONSE()
    }

    commentDataSource.addComment(queryBody)
    return ServiceResponses.OK()
  }

  @PUT
  @Path("/{commentId}")
  @Consumes(MediaType.APPLICATION_JSON)
  public Response changeCommentBasicData(@PathParam("commentId") int commentId, String queryBody) {

    if (ServiceUtils.checkIfArgumentsAreBlank(queryBody)) {
      return ServiceResponses.BLANK_ARGUMENTS_RESPONSE()
    }

    if (!commentDataSource.checkIfCommentExist(commentId)) {
      return ServiceResponses.GIVEN_COMMENT_DOESNT_EXIST_RESPONSE()
    }

    if (!ServiceUtils.validateJson(ServiceUtils.COMMENT_UPDATE_SCHEMA, queryBody)) {
      return ServiceResponses.ILLEGAL_JSON_RESPONSE()
    }

    commentDataSource.updateCommentInfo(commentId, queryBody)
    return ServiceResponses.OK()
  }
}