package com.januszsoft.kebabexplorer.anzen.services

import com.januszsoft.kebabexplorer.anzen.MongoTestRunner
import groovy.json.JsonSlurper
import org.skyscreamer.jsonassert.JSONAssert
import org.springframework.http.HttpMethod
import org.springframework.http.HttpStatus
import org.testng.annotations.AfterMethod
import org.testng.annotations.DataProvider
import org.testng.annotations.Test

public class UserTest extends MongoTestRunner {

//----------------------------------------------------------------------------------------------------------------------

  private static final String EXPECTED_ANSWERS_FILEPATH = "src/test/resources/expected/UserTest/"
  private static final String QUERY_URL = "http://localhost:8080/user/"

  @AfterMethod
  public void reloadDatabase() {
    super.reloadMocks()
  }

  def static getUserLogins() {
    def responseEntity = sendQuery("", QUERY_URL, HttpMethod.GET)
    assert responseEntity.getStatusCode() == HttpStatus.OK
    JsonSlurper slurper = new JsonSlurper()
    return slurper.parseText(responseEntity.getBody()).collect { it.login }.sort()
  }

//----------------------------------------------------------------------------------------------------------------------

  @DataProvider(name = "getUserTestDataProvider")
  public Object[][] getUserTestDataProvider() {
    [
      ["test1", HttpStatus.OK, readFileAsString(EXPECTED_ANSWERS_FILEPATH + "getUserTest/test1.json")],
      ["test2", HttpStatus.OK, readFileAsString(EXPECTED_ANSWERS_FILEPATH + "getUserTest/test2.json")],
      ["test3", HttpStatus.OK, readFileAsString(EXPECTED_ANSWERS_FILEPATH + "getUserTest/test3.json")],
      ["something", HttpStatus.NOT_FOUND, null]
    ]
  }

  @Test(dataProvider = "getUserTestDataProvider")
  public void getUserTest(String userLogin, HttpStatus expectedStatus, String expectedAnswer) throws IOException {
    def responseEntity = sendQuery("", QUERY_URL + userLogin, HttpMethod.GET)
    assert responseEntity.getStatusCode() == expectedStatus

    if (expectedStatus == HttpStatus.OK) {
      JSONAssert.assertEquals(responseEntity.getBody(), expectedAnswer, false)
    }
  }

//----------------------------------------------------------------------------------------------------------------------

  @Test
  public void getAllUsersTest() {
    def responseEntity = sendQuery("", QUERY_URL, HttpMethod.GET)
    assert responseEntity.getStatusCode() == HttpStatus.OK
    JSONAssert.assertEquals(responseEntity.getBody(), readFileAsString(EXPECTED_ANSWERS_FILEPATH + "getAllUsersTest/allUsers.json"), false)
  }

//----------------------------------------------------------------------------------------------------------------------

  def addUserTest(String userLogin, String queryBody, HttpStatus expectedStatus) {
    def responseEntity = sendQuery(queryBody, QUERY_URL + userLogin, HttpMethod.POST)
    assert responseEntity.getStatusCode() == expectedStatus

    if (expectedStatus == HttpStatus.OK) {
      getUserTest (userLogin, HttpStatus.OK, queryBody)
    }
  }

  @Test
  public void addUserTest() {
    assert getUserLogins() == ["test1", "test2", "test3"]
    addUserTest("Something", "", HttpStatus.BAD_REQUEST)
    assert getUserLogins() == ["test1", "test2", "test3"]
    addUserTest("Something", null, HttpStatus.BAD_REQUEST)
    assert getUserLogins() == ["test1", "test2", "test3"]
    addUserTest("test1", readFileAsString(EXPECTED_ANSWERS_FILEPATH + "getUserTest/test1.json"), HttpStatus.CONFLICT)
    assert getUserLogins() == ["test1", "test2", "test3"]
    addUserTest("test4", readFileAsString(EXPECTED_ANSWERS_FILEPATH + "addUserTest/test4.json"), HttpStatus.OK)
    assert getUserLogins() == ["test1", "test2", "test3", "test4"]
    addUserTest("test4", readFileAsString(EXPECTED_ANSWERS_FILEPATH + "addUserTest/test4.json"), HttpStatus.CONFLICT)
    assert getUserLogins() == ["test1", "test2", "test3", "test4"]
  }

//----------------------------------------------------------------------------------------------------------------------

  @DataProvider(name = "shouldNotAddUserAgainstSchemaDataProvider")
  public Object[][] shouldNotAddUserAgainstSchemaDataProvider() {
    [
      [readFileAsString(EXPECTED_ANSWERS_FILEPATH + "addSchemaCheck/bad_age.json")],
      [readFileAsString(EXPECTED_ANSWERS_FILEPATH + "addSchemaCheck/bad_age_2.json")],
      [readFileAsString(EXPECTED_ANSWERS_FILEPATH + "addSchemaCheck/bad_email.json")],
      [readFileAsString(EXPECTED_ANSWERS_FILEPATH + "addSchemaCheck/missing_required_fields.json")]
    ]
  }

  @Test(dataProvider = "shouldNotAddUserAgainstSchemaDataProvider")
  public void shouldNotAddUserAgainstSchema(String queryBody) {
    def responseEntity = sendQuery(queryBody, QUERY_URL + "test5", HttpMethod.POST)

    assert responseEntity.getStatusCode() == HttpStatus.BAD_REQUEST
  }

//----------------------------------------------------------------------------------------------------------------------

  def static deleteUserTest(String userLogin, HttpStatus expectedStatus) {
    def responseEntity = sendQuery("", QUERY_URL + userLogin, HttpMethod.DELETE)
    assert responseEntity.getStatusCode() == expectedStatus
  }

  @Test
  public void deleteUserTest() {
    assert getUserLogins() == ["test1", "test2", "test3"]
    deleteUserTest("Something", HttpStatus.NOT_FOUND)
    assert getUserLogins() == ["test1", "test2", "test3"]
    deleteUserTest("test3", HttpStatus.OK)
    assert getUserLogins() == ["test1", "test2"]
    deleteUserTest("test3", HttpStatus.NOT_FOUND)
    assert getUserLogins() == ["test1", "test2"]
  }

//----------------------------------------------------------------------------------------------------------------------

  @Test
  public void addAndDeleteUserTest() {

    assert getUserLogins() == ["test1", "test2", "test3"]

    for (int i = 0; i < 2; i++) {
      addUserTest("test4", readFileAsString(EXPECTED_ANSWERS_FILEPATH + "addUserTest/test4.json"), HttpStatus.OK)
      assert getUserLogins() == ["test1", "test2", "test3", "test4"]
      deleteUserTest("test4", HttpStatus.OK)
      assert getUserLogins() == ["test1", "test2", "test3"]
      deleteUserTest("test4", HttpStatus.NOT_FOUND)
      assert getUserLogins() == ["test1", "test2", "test3"]
    }

    assert getUserLogins() == ["test1", "test2", "test3"]
    deleteUserTest("test3", HttpStatus.OK)
    assert getUserLogins() == ["test1", "test2"]
    deleteUserTest("test2", HttpStatus.OK)
    assert getUserLogins() == ["test1"]
    deleteUserTest("test1", HttpStatus.OK)
    assert getUserLogins() == []
  }

//----------------------------------------------------------------------------------------------------------------------

  @DataProvider(name = "changeUserBasicDataDataProvider")
  public Object[][] changeUserBasicDataDataProvider() {
    [
      ["Something", '{"A":"B"}', HttpStatus.NOT_FOUND, null],
      ["test1", null, HttpStatus.BAD_REQUEST, null],


      ["test1",
       readFileAsString(EXPECTED_ANSWERS_FILEPATH + "changeBasicData/change_fullname_query.json"),
       HttpStatus.OK,
       readFileAsString(EXPECTED_ANSWERS_FILEPATH + "changeBasicData/change_fullname_answer.json"),
      ],

      ["test1",
       readFileAsString(EXPECTED_ANSWERS_FILEPATH + "changeBasicData/change_email_query.json"),
       HttpStatus.OK,
       readFileAsString(EXPECTED_ANSWERS_FILEPATH + "changeBasicData/change_email_answer.json"),
      ],

      ["test1",
       readFileAsString(EXPECTED_ANSWERS_FILEPATH + "changeBasicData/change_age_query.json"),
       HttpStatus.OK,
       readFileAsString(EXPECTED_ANSWERS_FILEPATH + "changeBasicData/change_age_answer.json"),
      ]
    ]
  }

  @Test(dataProvider = "changeUserBasicDataDataProvider")
  public void changeUserBasicData(String userLogin, String queryBody, HttpStatus expectedStatus, String expectedAnswer) {

    def responseEntity = sendQuery(queryBody, QUERY_URL + userLogin, HttpMethod.PUT)
    assert responseEntity.getStatusCode() == expectedStatus

    if (expectedStatus == HttpStatus.OK) {
      getUserTest(userLogin, HttpStatus.OK, expectedAnswer);
    }
  }

//----------------------------------------------------------------------------------------------------------------------

  @DataProvider(name = "shouldNotChangeUserInformationAgainstSchemaDataProvider")
  public Object[][] shouldNotChangeUserInformationAgainstSchemaDataProvider() {
    [
      [readFileAsString(EXPECTED_ANSWERS_FILEPATH + "updateSchemaCheck/bad_age.json")],
      [readFileAsString(EXPECTED_ANSWERS_FILEPATH + "updateSchemaCheck/bad_age_2.json")],
      [readFileAsString(EXPECTED_ANSWERS_FILEPATH + "updateSchemaCheck/bad_email.json")],
      [readFileAsString(EXPECTED_ANSWERS_FILEPATH + "updateSchemaCheck/bad_fullname.json")]
    ]
  }

  @Test(dataProvider = "shouldNotChangeUserInformationAgainstSchemaDataProvider")
  public void shouldNotChangeUserInformationAgainstSchema(String queryBody) {
    def responseEntity = sendQuery(queryBody, QUERY_URL + "test3", HttpMethod.PUT)

    assert responseEntity.getStatusCode() == HttpStatus.BAD_REQUEST
  }

}