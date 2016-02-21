package com.januszsoft.kebabexplorer.anzen.services

import com.januszsoft.kebabexplorer.anzen.datasource.SessionDataSource
import com.januszsoft.kebabexplorer.anzen.datasource.UserDataSource
import com.januszsoft.kebabexplorer.anzen.utils.ServiceResponses
import org.springframework.beans.factory.annotation.Autowired
import org.springframework.stereotype.Component

import javax.ws.rs.CookieParam
import javax.ws.rs.POST
import javax.ws.rs.Path
import javax.ws.rs.Produces
import javax.ws.rs.core.MediaType
import javax.ws.rs.core.NewCookie
import javax.ws.rs.core.Response

@Component
@Path("/logout")
@Produces(MediaType.APPLICATION_JSON)
public class Logout {

  @Autowired
  UserDataSource userDataSource

  @Autowired
  SessionDataSource sessionDataSource

  @POST
  @Path("/")
  public Response login(@CookieParam("kebab-explorer-login-cookie") String tokenHash) {

    if (!tokenHash) {
      return ServiceResponses.ALREADY_LOGGED_OUT_RESPONSE();
    }

    sessionDataSource.deleteToken(tokenHash)

    def responseCookie = new NewCookie("kebab-explorer-login-cookie",
        "", "/", "", "kebab-explorer-login-cookie", 0, false);

    return Response.ok(["message" : "User successfully logged out!"])
      .type(MediaType.APPLICATION_JSON).cookie(responseCookie).build();
  }


}