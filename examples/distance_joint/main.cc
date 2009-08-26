#include <cluttermm.h>
#include <clutter-box2dmm.h>
#include <iostream>



int main(int argc, char *argv[])
{

 try
  {
    // TODO: Pass context to init as soon as that init() overload has been
    // uncommented in cluttermm. This depends on a clutter release with
    // clutter bug #1033 fixed.
    // initialize the C++ wrapper types
    Clutter::init(&argc, &argv); //, context);
  }
  catch(const Glib::Exception& ex)
  {
    std::cerr << "Failed to initialize clutter: " << ex.what() << std::endl;
    return -1;
  }

  Glib::RefPtr<Clutter::Stage> stage = Clutter::Stage::get_default();
  stage->set_color( Clutter::Color(0x00, 0x00, 0x00, 0xff) );
  stage->set_size(800, 600);
  stage->set_title("Clutter::Box2D Example");

  Glib::RefPtr<Clutter::Box2D::Box2D> box2d = Clutter::Box2D::Box2D::create();
  stage->add_actor(box2d);

  //Add a actor around which the logo will rotate:
  Glib::RefPtr<Clutter::Rectangle> rect = Clutter::Rectangle::create();
  box2d->add_actor(rect);
  rect->set_size(10, 10);
  rect->set_position(stage->get_width() / 2, stage->get_height() / 2);
  box2d->set_child_mode(rect, Clutter::Box2D::BOX2D_STATIC); //It does not move.

  //Add an actor that can rotate around the central actor:
  Glib::RefPtr<Clutter::Texture> texture = Clutter::Texture::create();
  texture->set_from_file("gnome_logo.png");
  box2d->add_actor(texture);
  texture->set_opacity(1.0 * 255);
  texture->set_position(stage->get_width() / 2, 0); //It will be placed closer to the rect by the distance joint.
  box2d->set_child_mode(texture, Clutter::Box2D::BOX2D_DYNAMIC); //It moves.
  box2d->set_child_manipulatable(texture); //It can be moved with the mouse.
  
  //Add a distance joint, with points in the middle of each actor.
  //The dynamic actor will then move in a circle around the static one,
  //when manipulated with the mouse:
  Clutter::Vertex anchor1( rect->get_width()/2, rect->get_height()/2, 0 );
  Clutter::Vertex anchor2( texture->get_width()/2, texture->get_height()/2, 0);
  box2d->add_distance_joint(rect, texture, anchor1, anchor2, 200.0);

  box2d->property_gravity() = Clutter::Vertex(0, 0, 0);
  box2d->set_simulating();

  stage->show();

  Clutter::main();

  return 0;
}
