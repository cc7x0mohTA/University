package com.januszsoft.kebabexplorer.anzen;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;


@SpringBootApplication
public class AppRunner implements CommandLineRunner {

  private Logger logger = LoggerFactory.getLogger(AppRunner.class);

  public static void main(String[] args) {
    SpringApplication.run(AppRunner.class, args);
  }

  @Override
  public void run(String... args) throws Exception {
    logger.info("App started.");
  }
}