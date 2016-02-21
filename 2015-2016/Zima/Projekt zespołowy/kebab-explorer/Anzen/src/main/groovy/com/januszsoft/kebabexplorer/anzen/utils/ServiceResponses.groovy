package com.januszsoft.kebabexplorer.anzen.utils

import javax.ws.rs.core.MediaType
import javax.ws.rs.core.Response

public class ServiceResponses {

  def static createResponse(Response.Status status, body) {
    Response.status(status).entity(body).type(MediaType.APPLICATION_JSON).build()
  }

  def static BLANK_ARGUMENTS_RESPONSE() {
    createResponse(Response.Status.BAD_REQUEST, ["Message": "Arguments mustn\'t be blank!"])
  }

  def static ILLEGAL_JSON_RESPONSE() {
    createResponse(Response.Status.BAD_REQUEST, ["Message": "Illegal Json format!"])
  }

  def static GIVEN_RESTAURANT_EXIST_RESPONSE() {
    createResponse(Response.Status.CONFLICT, ["Message": "Given restaurant exists!"])
  }

  def static GIVEN_RESTAURANT_DOESNT_EXIST_RESPONSE() {
    createResponse(Response.Status.NOT_FOUND, ["Message": "Given restaurant doesn\'t exists!"])
  }

  def static GIVEN_SESSION_DOESNT_EXIST_RESPONSE() {
    createResponse(Response.Status.NOT_FOUND, ["Message": "Given session doesn\'t exists!"])
  }

  def static GIVEN_COMMENT_DOESNT_EXIST_RESPONSE() {
    createResponse(Response.Status.NOT_FOUND, ["Message": "Given comment doesn\'t exists!"])
  }


  def static GIVEN_USER_EXIST_RESPONSE() {
    createResponse(Response.Status.CONFLICT, ["Message": "Given user exists!"])
  }

  def static GIVEN_USER_DOESNT_EXIST_RESPONSE() {
    createResponse(Response.Status.NOT_FOUND, ["Message": "Given user doesn\'t exists!"])
  }

  def static UNAUTHORISED_USER_RESPONSE() {
    createResponse(Response.Status.UNAUTHORIZED, ["Message": "Unauthorised user!"])
  }


  def static ALREADY_LOGGED_OUT_RESPONSE() {
    createResponse(Response.Status.UNAUTHORIZED, ["Message": "User is already logged out!"])
  }

  def static OK() {
    Response.ok().build();
  }

  def static Response OK_RESPONSE_WITH_BODY(json) {
    createResponse(Response.Status.OK, json)
  }
}
