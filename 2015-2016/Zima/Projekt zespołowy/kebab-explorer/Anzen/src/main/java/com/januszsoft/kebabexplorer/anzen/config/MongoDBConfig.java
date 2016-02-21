package com.januszsoft.kebabexplorer.anzen.config;

import com.mongodb.DBCollection;
import com.mongodb.Mongo;
import com.mongodb.MongoClient;
import com.mongodb.WriteConcern;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.data.authentication.UserCredentials;
import org.springframework.data.mongodb.MongoDbFactory;
import org.springframework.data.mongodb.config.AbstractMongoConfiguration;
import org.springframework.data.mongodb.core.MongoTemplate;
import org.springframework.data.mongodb.core.SimpleMongoDbFactory;
import org.springframework.data.mongodb.repository.config.EnableMongoRepositories;

import java.net.UnknownHostException;

@Configuration
@EnableMongoRepositories(basePackages = "com.januszsoft.kebabexplorer.*")
public class MongoDBConfig extends AbstractMongoConfiguration {

  private static final String DATABASE_NAME = "januszsoft";
  private static final String DATABASE_HOST = "localhost";
  private static final String USERNAME = "";
  private static final String PASSWORD = "";
  private static final int DATABASE_PORT = 27017;
  public static final String RESTAURANT_COLLECTION_NAME = "Restaurant";
  public static final String USER_COLLECTION_NAME = "User";
  public static final String COMMENT_COLLECTION_NAME = "Comment";
  public static final String SESSION_COLLECTION_NAME = "Session";


  @Override
  protected String getDatabaseName() {
    return DATABASE_NAME;
  }

  @Bean
  @Override
  public Mongo mongo() throws UnknownHostException {
    MongoClient mongoClient = new MongoClient(DATABASE_HOST, DATABASE_PORT);
    mongoClient.setWriteConcern(WriteConcern.SAFE);
    return mongoClient;
  }

  @Bean
  public MongoDbFactory mongoDbFactory() throws UnknownHostException {
    UserCredentials userCredentials = new UserCredentials(USERNAME, PASSWORD);
    return new SimpleMongoDbFactory(mongo(), DATABASE_NAME, userCredentials);
  }

  @Bean(name = "mongoTemplate")
  public MongoTemplate mongoTemplate() throws UnknownHostException {
    MongoTemplate mongoTemplate = new MongoTemplate(mongoDbFactory());
    return mongoTemplate;
  }

  @Bean(name = "restaurantCollection")
  public DBCollection restaurantCollection() throws UnknownHostException {
    MongoTemplate mongoTemplate = mongoTemplate();
    DBCollection restaurants = mongoTemplate.getCollection(RESTAURANT_COLLECTION_NAME);
    return restaurants;
  }

  @Bean(name = "userCollection")
  public DBCollection userCollection() throws UnknownHostException {
    MongoTemplate mongoTemplate = mongoTemplate();
    DBCollection users = mongoTemplate.getCollection(USER_COLLECTION_NAME);
    return users;
  }

  @Bean(name = "commentCollection")
  public DBCollection opinionCollection() throws UnknownHostException {
    MongoTemplate mongoTemplate = mongoTemplate();
    DBCollection comments = mongoTemplate.getCollection(COMMENT_COLLECTION_NAME);
    return comments;
  }

  @Bean(name = "sessionCollection")
  public DBCollection sessionCollection() throws UnknownHostException {
    MongoTemplate mongoTemplate = mongoTemplate();
    DBCollection sessions = mongoTemplate.getCollection(SESSION_COLLECTION_NAME);
    return sessions;
  }
}