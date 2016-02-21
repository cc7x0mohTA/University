package com.januszsoft.kebabexplorer.anzen;

import com.google.common.base.Charsets;
import com.google.common.io.Files;
import com.januszsoft.kebabexplorer.anzen.config.EmbedMongoConfig;
import org.springframework.boot.test.SpringApplicationConfiguration;
import org.springframework.boot.test.TestRestTemplate;
import org.springframework.boot.test.WebIntegrationTest;
import org.springframework.http.*;
import org.springframework.test.annotation.DirtiesContext;
import org.springframework.test.context.testng.AbstractTestNGSpringContextTests;
import org.testng.annotations.AfterSuite;
import org.testng.annotations.BeforeSuite;

import java.io.File;
import java.io.IOException;
import java.nio.charset.Charset;

@SpringApplicationConfiguration(classes = AppRunner.class)
@WebIntegrationTest
@DirtiesContext
public class MongoTestRunner extends AbstractTestNGSpringContextTests {

  @BeforeSuite
  public void setUpTestEnvironment() throws IOException {
    EmbedMongoConfig.setUpEmbedMongo();
  }

  @AfterSuite
  public void tearDown() throws Exception {
    EmbedMongoConfig.tearEmbedMongoDown();
  }

  public void reloadMocks() throws IOException {
    EmbedMongoConfig.reloadRestaurantsMocks();
    EmbedMongoConfig.reloadUsersMocks();
  }

  public static ResponseEntity<String> sendQuery(String body, String query, HttpMethod httpMethod) {
    HttpHeaders headers = new HttpHeaders();
    MediaType mediaType = new MediaType("application", "json", Charset.forName("UTF-8"));
    headers.setContentType(mediaType);
    HttpEntity<String> entity = new HttpEntity<>(body, headers);
    return new TestRestTemplate("test", "test").exchange(query, httpMethod, entity, String.class);
  }

  public static String readFileAsString(String filePath) throws IOException {
    File file = new File(filePath);
    return Files.toString(file, Charsets.UTF_8);
  }
}