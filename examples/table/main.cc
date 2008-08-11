#include <cluttermm.h>
#include <clutter-box2dmm.h>
#include <iostream>

static void
add_static_box(const Glib::RefPtr<Clutter::Box2D::Box2D>& box2d,
                int x, int y, int width, int height)
{
  Glib::RefPtr<Clutter::Rectangle> rect = Clutter::Rectangle::create();
  rect->set_size(width, height);
  rect->set_position(x, y);

  box2d->add_actor(rect);
  box2d->set_child_mode(rect, Clutter::Box2D::BOX2D_STATIC);
}

void
add_cage(const Glib::RefPtr<Clutter::Box2D::Box2D>& box2d, bool roof)
{
  Glib::RefPtr<Clutter::Stage> stage = Clutter::Stage::get_default(); //TODO: There could be more than one stage.
  const int width = stage->get_width();
  const int height = stage->get_height();

  if(roof)
    add_static_box(box2d, -100, -100, width + 200, 100);
  else
    add_static_box(box2d, -100, -height*(3-1)-100, width + 200, 100);
 
  add_static_box(box2d, -100, height, width + 200, 100);

  add_static_box(box2d, -100, -(height*(5-1)) , 100, height * 5);
  add_static_box(box2d, width, -(height*(5-1)) , 100, height * 5);
}


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
  box2d->set_simulating();
  box2d->property_gravity() = Clutter::Vertex(0, 0, 0);
  
  add_cage(box2d, true /* roof */);

  for(int i = 42; i >= 0; --i)
  {
    const int x = stage->get_width() / 2;
    const int y = stage->get_height() * 0.8;

    Glib::RefPtr<Clutter::Texture> texture = Clutter::Texture::create();
    texture->set_from_file("gnome_logo.png");
    box2d->add_actor(texture);
    texture->set_opacity(1.0 * 255);
    texture->set_position(x, y);

    box2d->set_child_manipulatable(texture);
    box2d->set_child_mode(texture, Clutter::Box2D::BOX2D_DYNAMIC);
  }

  stage->show();

  Clutter::main();

  return 0;
}
