package com.januszsoft.kebabexplorer.anzen.config;

import com.beust.jcommander.internal.Lists;
import com.mongodb.*;
import de.flapdoodle.embed.mongo.MongodExecutable;
import de.flapdoodle.embed.mongo.MongodProcess;
import de.flapdoodle.embed.mongo.MongodStarter;
import de.flapdoodle.embed.mongo.config.IMongodConfig;
import de.flapdoodle.embed.mongo.config.MongodConfigBuilder;
import de.flapdoodle.embed.mongo.config.Net;
import de.flapdoodle.embed.mongo.distribution.Version;
import de.flapdoodle.embed.process.runtime.Network;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.List;

public class EmbedMongoConfig {

//----------------------------------------------------------------------------------------------------------------------

  private static final String MOCK_PATH = "src/test/resources/mock/";
  private static final int PORT = 27017;
  private static final String HOSTNAME = "localhost";
  private static final String DATABASENAME = "januszsoft";
  private static final String RESTAURANT_COLLECTION_NAME = "Restaurant";
  private static final String USER_COLLECTION_NAME = "User";
  private static final String COMMENT_COLLECTION_NAME = "Comment";

//----------------------------------------------------------------------------------------------------------------------

  private static MongodExecutable mongodExe;
  private static MongodProcess mongod;
  private static MongoClient mongo;
  private static DB db;
  private static boolean running = false;

//----------------------------------------------------------------------------------------------------------------------

  public static void setUpEmbedMongo() throws IOException {

    MongodStarter starter = MongodStarter.getDefaultInstance();

    IMongodConfig mongodConfig = new MongodConfigBuilder()
      .version(Version.Main.PRODUCTION)
      .net(new Net(PORT, Network.localhostIsIPv6()))
      .build();

    mongodExe = starter.prepare(mongodConfig);
    mongod = mongodExe.start();
    mongo = new MongoClient(HOSTNAME, PORT);
    db = mongo.getDB(DATABASENAME);
    running = true;

    reloadRestaurantsMocks();
    reloadUsersMocks();
    reloadCommentMocks();

    DBObject locationIndex = new BasicDBObject("location", "2dsphere");
    db.getCollection(RESTAURANT_COLLECTION_NAME).createIndex(locationIndex);
  }

  public static void tearEmbedMongoDown() {
    mongod.stop();
    mongodExe.stop();
  }

  public static void reloadRestaurantsMocks() throws IOException {

    if (!running) return;

    if (db.collectionExists(RESTAURANT_COLLECTION_NAME)) {
      db.getCollection(RESTAURANT_COLLECTION_NAME).drop();
    }

    db.createCollection(RESTAURANT_COLLECTION_NAME, new BasicDBObject());
    DBCollection restaurants = db.getCollection(RESTAURANT_COLLECTION_NAME);
    List<String> restaurantNames = Lists.newArrayList("kalimera", "kavos", "le_gyros", "ramzes_I");

    for (String restaurantName : restaurantNames) {
      String json = new String(Files.readAllBytes(Paths.get(MOCK_PATH + "restaurants/" + restaurantName + ".json")));
      DBObject dbObject = (DBObject) com.mongodb.util.JSON.parse(json);
      restaurants.insert(dbObject);
    }
  }

  public static void reloadUsersMocks() throws IOException {

    if (!running) return;

    if (db.collectionExists(USER_COLLECTION_NAME)) {
      db.getCollection(USER_COLLECTION_NAME).drop();
    }

    db.createCollection(USER_COLLECTION_NAME, new BasicDBObject());
    DBCollection users = db.getCollection(USER_COLLECTION_NAME);
    List<String> userLogins = Lists.newArrayList("test1", "test2", "test3");

    for (String userLogin : userLogins) {
      String json = new String(Files.readAllBytes(Paths.get(MOCK_PATH + "users/" + userLogin + ".json")));
      DBObject dbObject = (DBObject) com.mongodb.util.JSON.parse(json);
      users.insert(dbObject);
    }
  }

  public static void reloadCommentMocks() throws IOException {

    if (!running) return;

    if (db.collectionExists(COMMENT_COLLECTION_NAME)) {
      db.getCollection(COMMENT_COLLECTION_NAME).drop();
    }

    db.createCollection(COMMENT_COLLECTION_NAME, new BasicDBObject());
    DBCollection comments = db.getCollection(COMMENT_COLLECTION_NAME);
    List<String> commentsId = Lists.newArrayList("1", "2", "3", "4", "5");

    for (String commentId : commentsId) {
      String json = new String(Files.readAllBytes(Paths.get(MOCK_PATH + "comments/" + commentId + ".json")));
      DBObject dbObject = (DBObject) com.mongodb.util.JSON.parse(json);
      comments.insert(dbObject);
    }
  }

  private EmbedMongoConfig() {
  }

//----------------------------------------------------------------------------------------------------------------------

}
