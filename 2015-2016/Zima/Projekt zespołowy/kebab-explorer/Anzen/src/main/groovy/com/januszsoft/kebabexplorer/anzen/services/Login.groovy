package com.januszsoft.kebabexplorer.anzen.services

import com.januszsoft.kebabexplorer.anzen.datasource.SessionDataSource
import com.januszsoft.kebabexplorer.anzen.datasource.UserDataSource
import com.januszsoft.kebabexplorer.anzen.utils.ServiceResponses
import com.januszsoft.kebabexplorer.anzen.utils.ServiceUtils
import org.springframework.beans.factory.annotation.Autowired
import org.springframework.stereotype.Component

import javax.ws.rs.GET
import javax.ws.rs.POST
import javax.ws.rs.Path
import javax.ws.rs.PathParam
import javax.ws.rs.Produces
import javax.ws.rs.QueryParam
import javax.ws.rs.core.Cookie
import javax.ws.rs.core.MediaType
import javax.ws.rs.core.NewCookie
import javax.ws.rs.core.Response

@Component
@Path("/login")
@Produces(MediaType.APPLICATION_JSON)
public class Login {

  @Autowired
  UserDataSource userDataSource

  @Autowired
  SessionDataSource sessionDataSource

  @GET
  @Path("/{cookieHash}")
  public Response getSessionInfo(@PathParam("cookieHash") String cookieHash) {

    if (ServiceUtils.checkIfArgumentsAreBlank(cookieHash)) {
      return ServiceResponses.BLANK_ARGUMENTS_RESPONSE()
    }

    if (!sessionDataSource.checkIfSessionExist(cookieHash)) {
      return ServiceResponses.GIVEN_SESSION_DOESNT_EXIST_RESPONSE()
    }

    return ServiceResponses.OK_RESPONSE_WITH_BODY(sessionDataSource.getSessionInfo(cookieHash))
  }

  @POST
  @Path("/")
  public Response login(@QueryParam("userLogin") String userLogin,
                        @QueryParam("passwordHash") String passwordHash) {

    if (ServiceUtils.checkIfArgumentsAreBlank(userLogin, passwordHash)) {
      return ServiceResponses.BLANK_ARGUMENTS_RESPONSE()
    }

    if (!userDataSource.checkIfUserExist(userLogin)) {
      return ServiceResponses.GIVEN_USER_DOESNT_EXIST_RESPONSE()
    }

    if (userDataSource.getPasswordHash(userLogin) != passwordHash) {
      return ServiceResponses.UNAUTHORISED_USER_RESPONSE()
    }

    def token = sessionDataSource.generateAndInsertToken(userLogin)

    def responseCookie = new NewCookie("kebab-explorer-login-cookie",
        (String) token["hash"], "/", "", "kebab-explorer-login-cookie", 60*60*24, false);

    return Response.ok(token.toString())
      .type(MediaType.APPLICATION_JSON).cookie(responseCookie).build();
  }


}