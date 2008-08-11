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
  

  add_cage(box2d, true /* roof */);

  const int y = stage->get_height() / 2;
  int num_planks = stage->get_width() / 20 - 2;
  Glib::RefPtr<Clutter::Rectangle> rect = Clutter::Rectangle::create();
  rect->set_size(18, 5);
  rect->set_position(10, y);
  box2d->add_actor(rect);

  box2d->set_child_mode(rect, Clutter::Box2D::BOX2D_STATIC);

  Glib::RefPtr<Clutter::Actor> prev_actor = rect;

  for(int i = 0; i < num_planks; ++i)
  {
    Glib::RefPtr<Clutter::Rectangle> box = Clutter::Rectangle::create();
    box->set_size(18, 5);
    box->set_position(20 + 20 * i, y);
    box2d->add_actor(box);

    box2d->set_child_manipulatable(box, true);
    box2d->set_child_mode(box, Clutter::Box2D::BOX2D_DYNAMIC);

    Clutter::Vertex anchor( CLUTTER_UNITS_FROM_FLOAT (20 + 20 * i), CLUTTER_UNITS_FROM_FLOAT (y), 0 );
    box2d->add_revolute_joint(prev_actor, box, anchor);
   
    prev_actor = box;
  }

  Glib::RefPtr<Clutter::Rectangle> box = Clutter::Rectangle::create();
  box->set_size(18, 5);
  box->set_position(20 + 20 * num_planks, y);
  box2d->add_actor(box);

  box2d->set_child_mode(box, Clutter::Box2D::BOX2D_STATIC);

  Clutter::Vertex anchor( CLUTTER_UNITS_FROM_FLOAT (20 + 20 * num_planks), CLUTTER_UNITS_FROM_FLOAT (y), 0 );
  box2d->add_revolute_joint(prev_actor, box, anchor);

  box2d->set_simulating();

  stage->show();

  Clutter::main();

  return 0;
}
