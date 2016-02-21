package com.januszsoft.kebabexplorer.anzen.services

import com.januszsoft.kebabexplorer.anzen.MongoTestRunner
import groovy.json.JsonSlurper
import org.skyscreamer.jsonassert.JSONAssert
import org.springframework.http.HttpMethod
import org.springframework.http.HttpStatus
import org.testng.annotations.AfterMethod
import org.testng.annotations.DataProvider
import org.testng.annotations.Test

public class RestaurantTest extends MongoTestRunner {

//----------------------------------------------------------------------------------------------------------------------

  private static final String EXPECTED_ANSWERS_FILEPATH = "src/test/resources/expected/RestaurantTest/"
  private static final String QUERY_URL = "http://localhost:8080/restaurant/"

  @AfterMethod
  public void reloadDatabase() {
    super.reloadMocks()
  }

  def static getRestaurantNames() {
    def responseEntity = sendQuery("", QUERY_URL, HttpMethod.GET)
    assert responseEntity.getStatusCode() == HttpStatus.OK
    JsonSlurper slurper = new JsonSlurper()
    return slurper.parseText(responseEntity.getBody()).collect { it.name }.sort()
  }

//----------------------------------------------------------------------------------------------------------------------

  @DataProvider(name = "getRestaurantTestDataProvider")
  public Object[][] getRestaurantTestDataProvider() {
    [
      ["kalimera", HttpStatus.OK, readFileAsString(EXPECTED_ANSWERS_FILEPATH + "getRestaurantTest/kalimera.json")],
      ["kavos", HttpStatus.OK, readFileAsString(EXPECTED_ANSWERS_FILEPATH + "getRestaurantTest/kavos.json")],
      ["le_gyros", HttpStatus.OK, readFileAsString(EXPECTED_ANSWERS_FILEPATH + "getRestaurantTest/le_gyros.json")],
      ["ramzes_I", HttpStatus.OK, readFileAsString(EXPECTED_ANSWERS_FILEPATH + "getRestaurantTest/ramzes_I.json")],
      ["something", HttpStatus.NOT_FOUND, null]
    ]
  }

  @Test(dataProvider = "getRestaurantTestDataProvider")
  public void getRestaurantTest(String restaurantName, HttpStatus expectedStatus, String expectedAnswer) throws IOException {
    def responseEntity = sendQuery("", QUERY_URL + restaurantName, HttpMethod.GET)
    assert responseEntity.getStatusCode() == expectedStatus

    if (expectedStatus == HttpStatus.OK) {
      JSONAssert.assertEquals(responseEntity.getBody(), expectedAnswer, false)
    }
  }

//----------------------------------------------------------------------------------------------------------------------

  @Test
  public void getAllRestaurantTest() {
    def responseEntity = sendQuery("", QUERY_URL, HttpMethod.GET)
    assert responseEntity.getStatusCode() == HttpStatus.OK
    JSONAssert.assertEquals(responseEntity.getBody(), readFileAsString(EXPECTED_ANSWERS_FILEPATH + "getAllRestaurantsTest/allRestaurants.json"), false)
  }

//----------------------------------------------------------------------------------------------------------------------

  def addRestaurantTest(String restaurantName, String queryBody, HttpStatus expectedStatus) {
    def responseEntity = sendQuery(queryBody, QUERY_URL + restaurantName, HttpMethod.POST)
    assert responseEntity.getStatusCode() == expectedStatus

    if (expectedStatus == HttpStatus.OK) {
      getRestaurantTest(restaurantName, HttpStatus.OK, queryBody)
    }
  }

  @Test
  public void addRestaurantTest() {
    assert getRestaurantNames() == ["kalimera", "kavos", "le_gyros", "ramzes_I"]
    addRestaurantTest("Something", "", HttpStatus.BAD_REQUEST)
    assert getRestaurantNames() == ["kalimera", "kavos", "le_gyros", "ramzes_I"]
    addRestaurantTest("Something", null, HttpStatus.BAD_REQUEST)
    assert getRestaurantNames() == ["kalimera", "kavos", "le_gyros", "ramzes_I"]
    addRestaurantTest("kavos", readFileAsString(EXPECTED_ANSWERS_FILEPATH + "getRestaurantTest/kavos.json"), HttpStatus.CONFLICT)
    assert getRestaurantNames() == ["kalimera", "kavos", "le_gyros", "ramzes_I"]
    addRestaurantTest("kebab_king", readFileAsString(EXPECTED_ANSWERS_FILEPATH + "addRestaurantTest/kebab_king.json"), HttpStatus.OK)
    assert getRestaurantNames() == ["kalimera", "kavos", "kebab_king", "le_gyros", "ramzes_I"]
    addRestaurantTest("kebab_king", readFileAsString(EXPECTED_ANSWERS_FILEPATH + "addRestaurantTest/kebab_king.json"), HttpStatus.CONFLICT)
    assert getRestaurantNames() == ["kalimera", "kavos", "kebab_king", "le_gyros", "ramzes_I"]
  }

//----------------------------------------------------------------------------------------------------------------------

  @DataProvider(name = "shouldNotAddRestaurantAgainstSchemaDataProvider")
  public Object[][] shouldNotAddRestaurantAgainstSchemaDataProvider() {
    [
      [readFileAsString(EXPECTED_ANSWERS_FILEPATH + "addSchemaCheck/bad_city.json")],
      [readFileAsString(EXPECTED_ANSWERS_FILEPATH + "addSchemaCheck/bad_phone.json")],
      [readFileAsString(EXPECTED_ANSWERS_FILEPATH + "addSchemaCheck/bad_phone_2.json")],
      [readFileAsString(EXPECTED_ANSWERS_FILEPATH + "addSchemaCheck/bad_postcode.json")],
      [readFileAsString(EXPECTED_ANSWERS_FILEPATH + "addSchemaCheck/missing_required_fields.json")]
    ]
  }

  @Test(dataProvider = "shouldNotAddRestaurantAgainstSchemaDataProvider")
  public void shouldNotAddRestaurantAgainstSchema(String queryBody) {
    def responseEntity = sendQuery(queryBody, QUERY_URL + "some_new_restaurant", HttpMethod.POST)

    assert responseEntity.getStatusCode() == HttpStatus.BAD_REQUEST
  }

//----------------------------------------------------------------------------------------------------------------------

  def static deleteRestaurantTest(String restaurantName, HttpStatus expectedStatus) {
    def responseEntity = sendQuery("", QUERY_URL + restaurantName, HttpMethod.DELETE)
    assert responseEntity.getStatusCode() == expectedStatus
  }

  @Test
  public void deleteRestaurantTest() {
    assert getRestaurantNames() == ["kalimera", "kavos", "le_gyros", "ramzes_I"]
    deleteRestaurantTest("Something", HttpStatus.NOT_FOUND)
    assert getRestaurantNames() == ["kalimera", "kavos", "le_gyros", "ramzes_I"]
    deleteRestaurantTest("kavos", HttpStatus.OK)
    assert getRestaurantNames() == ["kalimera", "le_gyros", "ramzes_I"]
    deleteRestaurantTest("kavos", HttpStatus.NOT_FOUND)
    assert getRestaurantNames() == ["kalimera", "le_gyros", "ramzes_I"]
  }

//----------------------------------------------------------------------------------------------------------------------

  @Test
  public void addAndDeleteRestaurantTest() {

    assert getRestaurantNames() == ["kalimera", "kavos", "le_gyros", "ramzes_I"]

    for (int i = 0; i < 2; i++) {
      addRestaurantTest("kebab_king", readFileAsString(EXPECTED_ANSWERS_FILEPATH + "addRestaurantTest/kebab_king.json"), HttpStatus.OK)
      assert getRestaurantNames() == ["kalimera", "kavos", "kebab_king", "le_gyros", "ramzes_I"]
      deleteRestaurantTest("kebab_king", HttpStatus.OK)
      assert getRestaurantNames() == ["kalimera", "kavos", "le_gyros", "ramzes_I"]
      deleteRestaurantTest("kebab_king", HttpStatus.NOT_FOUND)
      assert getRestaurantNames() == ["kalimera", "kavos", "le_gyros", "ramzes_I"]
    }

    assert getRestaurantNames() == ["kalimera", "kavos", "le_gyros", "ramzes_I"]
    deleteRestaurantTest("kalimera", HttpStatus.OK)
    assert getRestaurantNames() == ["kavos", "le_gyros", "ramzes_I"]
    deleteRestaurantTest("kavos", HttpStatus.OK)
    assert getRestaurantNames() == ["le_gyros", "ramzes_I"]
    deleteRestaurantTest("le_gyros", HttpStatus.OK)
    assert getRestaurantNames() == ["ramzes_I"]
    deleteRestaurantTest("ramzes_I", HttpStatus.OK)
    assert getRestaurantNames() == []
  }

//----------------------------------------------------------------------------------------------------------------------

  @DataProvider(name = "changeRestaurantBasicDataDataProvider")
  public Object[][] changeRestaurantBasicDataDataProvider() {
    [
      ["Something", '{"A":"B"}', HttpStatus.NOT_FOUND, null],
      ["kavos", null, HttpStatus.BAD_REQUEST, null],

      ["kavos",
       readFileAsString(EXPECTED_ANSWERS_FILEPATH + "changeBasicData/change_adress_query.json"),
       HttpStatus.OK,
       readFileAsString(EXPECTED_ANSWERS_FILEPATH + "changeBasicData/change_adress_answer.json"),
      ],

      ["kavos",
       readFileAsString(EXPECTED_ANSWERS_FILEPATH + "changeBasicData/change_fullname_query.json"),
       HttpStatus.OK,
       readFileAsString(EXPECTED_ANSWERS_FILEPATH + "changeBasicData/change_fullname_answer.json"),
      ],

      ["kavos",
       readFileAsString(EXPECTED_ANSWERS_FILEPATH + "changeBasicData/change_email_query.json"),
       HttpStatus.OK,
       readFileAsString(EXPECTED_ANSWERS_FILEPATH + "changeBasicData/change_email_answer.json"),
      ],

      ["kavos",
       readFileAsString(EXPECTED_ANSWERS_FILEPATH + "changeBasicData/change_phone_query_1.json"),
       HttpStatus.OK,
       readFileAsString(EXPECTED_ANSWERS_FILEPATH + "changeBasicData/change_phone_answer_1.json"),
      ],

      ["kavos",
       readFileAsString(EXPECTED_ANSWERS_FILEPATH + "changeBasicData/change_phone_query_2.json"),
       HttpStatus.OK,
       readFileAsString(EXPECTED_ANSWERS_FILEPATH + "changeBasicData/change_phone_answer_2.json"),
      ],

      [
        "kalimera",
        readFileAsString(EXPECTED_ANSWERS_FILEPATH + "changeBasicData/add_email_query.json"),
        HttpStatus.OK,
        readFileAsString(EXPECTED_ANSWERS_FILEPATH + "changeBasicData/add_email_answer.json"),
      ]
    ]
  }

  @Test(dataProvider = "changeRestaurantBasicDataDataProvider")
  public void changeRestaurantBasicData(String restaurantName, String queryBody, HttpStatus expectedStatus, String expectedAnswer) {

    def responseEntity = sendQuery(queryBody, QUERY_URL + restaurantName, HttpMethod.PUT)
    assert responseEntity.getStatusCode() == expectedStatus

    if (expectedStatus == HttpStatus.OK) {
      getRestaurantTest(restaurantName, HttpStatus.OK, expectedAnswer);
    }
  }

//----------------------------------------------------------------------------------------------------------------------

  @DataProvider(name = "shouldNotChangeRestaurantInformationAgainstSchemaDataProvider")
  public Object[][] shouldNotChangeRestaurantInformationAgainstSchemaDataProvider() {
    [
      [readFileAsString(EXPECTED_ANSWERS_FILEPATH + "updateSchemaCheck/bad_city.json")],
      [readFileAsString(EXPECTED_ANSWERS_FILEPATH + "updateSchemaCheck/bad_phone.json")],
      [readFileAsString(EXPECTED_ANSWERS_FILEPATH + "updateSchemaCheck/bad_phone_2.json")],
      [readFileAsString(EXPECTED_ANSWERS_FILEPATH + "updateSchemaCheck/bad_postcode.json")]
    ]
  }

  @Test(dataProvider = "shouldNotChangeRestaurantInformationAgainstSchemaDataProvider")
  public void shouldNotChangeRestaurantInformationAgainstSchema(String queryBody) {
    def responseEntity = sendQuery(queryBody, QUERY_URL + "kalimera", HttpMethod.PUT)

    assert responseEntity.getStatusCode() == HttpStatus.BAD_REQUEST
  }

}