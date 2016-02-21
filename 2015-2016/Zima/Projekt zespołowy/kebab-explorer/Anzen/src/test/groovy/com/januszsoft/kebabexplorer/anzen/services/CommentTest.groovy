package com.januszsoft.kebabexplorer.anzen.services

import com.januszsoft.kebabexplorer.anzen.MongoTestRunner
import org.skyscreamer.jsonassert.JSONAssert
import org.springframework.http.HttpMethod
import org.springframework.http.HttpStatus
import org.testng.annotations.AfterMethod
import org.testng.annotations.DataProvider
import org.testng.annotations.Test

public class CommentTest extends MongoTestRunner {

  private static final String EXPECTED_ANSWERS_FILEPATH = "src/test/resources/expected/CommentTest/"
  private static final String QUERY_URL = "http://localhost:8080/comment"

  @AfterMethod
  public void reloadDatabase() {
    super.reloadMocks()
  }

  @DataProvider(name = "getAllCommentsTestDataProvider")
  public Object[][] getAllCommentsTestDataProvider() {
    [
      [QUERY_URL, "allComments.json"],
      [QUERY_URL + "?userName=bbednarczyk", "bbednarczyk.json"],
      [QUERY_URL + "?restaurantName=kavos&userName=bbednarczyk", "kavosbbednarczyk.json"],
      [QUERY_URL + "?userName=sth", "sth.json"]
    ]
  }

  @Test(dataProvider = "getAllCommentsTestDataProvider")
  public void getAllCommentsTest(String query, String filename) {
    def responseEntity = sendQuery("", query, HttpMethod.GET)
    assert responseEntity.getStatusCode() == HttpStatus.OK
    JSONAssert.assertEquals(responseEntity.getBody(), readFileAsString(EXPECTED_ANSWERS_FILEPATH + "getAllCommentsTest/" + filename), false)
   }
}