package com.januszsoft.kebabexplorer.anzen.config;

import com.januszsoft.kebabexplorer.anzen.services.*;
import org.glassfish.jersey.server.ResourceConfig;
import org.springframework.stereotype.Component;

import javax.ws.rs.ApplicationPath;

@Component
@ApplicationPath("/")
public class JerseyConfig extends ResourceConfig {
  public JerseyConfig() {
    register(Restaurant.class);
    register(User.class);
    register(Comment.class);
    register(Login.class);
    register(Logout.class);
  }
}