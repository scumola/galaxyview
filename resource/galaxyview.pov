#include "colors.inc"
#include "stones.inc"
#include "textures.inc"


/*
global_settings {
   assumed_gamma 1.2
}
*/


camera {
  location <0.1,0.1,-10>
  look_at <0,0.1,1>
  angle 36
}


light_source {<10, 1, -20> color White}
light_source {<5, 1.2, -20> color White}
light_source {<-5, 1, -20> color White}
light_source {<-10, 1.2, -20> color White}
light_source {<0, 0, 0> color White}
light_source {<0, 0, 0> color White}
light_source {<50, 1, -100> color LightGray}


text { ttf "timrom.ttf" "GalaxyView" 25, 0
  texture { Jade }
  translate <-3, 1.0 , 0.0>
}
