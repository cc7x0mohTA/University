package com.januszsoft.kebabexplorer.anzen.utils

import com.fasterxml.jackson.databind.ObjectMapper
import com.github.fge.jackson.JsonLoader
import com.github.fge.jsonschema.main.JsonSchemaFactory
import org.apache.commons.lang3.RandomStringUtils

import java.text.DateFormat
import java.text.SimpleDateFormat

class ServiceUtils {
  static final String PATH_TO_SCHEMES = "src/main/resources/jsonSchemes/"

  public static final String RESTAURANT_ADD_SCHEMA = "restaurantAddSchema.json"
  public static final String RESTAURANT_UPDATE_SCHEMA = "restaurantUpdateSchema.json"

  public static final String USER_ADD_SCHEMA = "userAddSchema.json"
  public static final String USER_UPDATE_SCHEMA = "userUpdateSchema.json"

  public static final String COMMENT_ADD_SCHEMA = "commentAddSchema.json"
  public static final String COMMENT_UPDATE_SCHEMA = "commentUpdateSchema.json"


  static boolean checkIfArgumentsAreBlank(Object... args) {
    return args.inject(false, { value, arg -> value || (!arg) })
  }

  static boolean validateJson(String schemaType, String json) {
    def objectMapper = new ObjectMapper()
    def currentJson = objectMapper.readTree(json)
    def schemaNode = JsonLoader.fromPath(PATH_TO_SCHEMES + schemaType)
    def schema = JsonSchemaFactory.byDefault().getJsonSchema(schemaNode)
    return schema.validate(currentJson).isSuccess()
  }

  static String generateRandomString(int minLength, int maxLength) {
    Random rand = new Random()
    def charset = (('a'..'z') + ('A'..'Z') + ('0'..'9')).join()
    def randomStringLength = minLength + rand.nextInt(maxLength - minLength + 1)
    def randomString = RandomStringUtils.random(randomStringLength, charset.toCharArray())
    return randomString
  }

  static String nextDayDate() {
    DateFormat dateFormat = new SimpleDateFormat("yyyy/MM/dd HH:mm:ss");
    Calendar cal = Calendar.getInstance();
    cal.add(Calendar.DATE, 1);
    return dateFormat.format(cal.getTime()).toString()
  }
}
