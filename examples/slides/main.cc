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
  stage->set_size(500, 500);
  stage->set_title("Clutter::Box2D Example");


  Glib::RefPtr<Clutter::Box2D::Box2D> box2d = Clutter::Box2D::Box2D::create();
  stage->add_actor(box2d);
  

  add_cage(box2d, false /* no roof */);


  Glib::RefPtr<Clutter::Rectangle> ground1 = Clutter::Rectangle::create();
  ground1->set_size(256, 3);
  ground1->set_position(0, 310);
  ground1->set_rotation(Clutter::Z_AXIS, 30.0, 128, 16, 0);
  box2d->add_actor(ground1);
  box2d->set_child_mode(ground1, Clutter::Box2D::BOX2D_STATIC);

  Glib::RefPtr<Clutter::Rectangle> ground2 = Clutter::Rectangle::create();
  ground2->set_size(256, 3);
  ground2->set_position(200, 200);
  ground2->set_rotation(Clutter::Z_AXIS, -30.0, 0, 0, 0);
  box2d->add_actor(ground2);
  box2d->set_child_mode(ground2, Clutter::Box2D::BOX2D_STATIC);


  for(int i = 0; i < 20; ++i)
  {
    const int x = g_random_int_range(0, stage->get_width());
    const int y = g_random_int_range(-(stage->get_height()), 0);

    Glib::RefPtr<Clutter::Texture> texture = Clutter::Texture::create();
    texture->set_from_file("gnome_logo.png");
    box2d->add_actor(texture);
    texture->set_opacity(1.0 * 255);
    texture->set_position(x, y);

    box2d->set_child_manipulatable(texture);
    box2d->set_child_mode(texture, Clutter::Box2D::BOX2D_DYNAMIC);
  }

  box2d->set_reactive();
  box2d->set_simulating();

  stage->show();

  Clutter::main();

  return 0;
}
