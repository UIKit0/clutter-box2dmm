#include <cluttermm.h>
#include <clutter-box2dmm.h>
#include <iostream>

static void
add_static_box(const Glib::RefPtr<Clutter::Container>& group,
                int x, int y, int width, int height)
{
  Glib::RefPtr<Clutter::Rectangle> rect = Clutter::Rectangle::create();
  rect->set_size(width, height);
  rect->set_position(x, y);
  group->add_actor(rect);

  group->set_child_property(rect, "mode", (int)Clutter::Box2D::BOX2D_STATIC);
}

void
add_cage (const Glib::RefPtr<Clutter::Container>& group, bool roof)
{
  Glib::RefPtr<Clutter::Stage> stage = Clutter::Stage::get_default(); //TODO: There could be more than one stage.
  int width = stage->get_width();
  int height = stage->get_height();

  if(roof)
    add_static_box(group, -100, -100, width + 200, 100);
  else
    add_static_box(group, -100, -height*(3-1)-100, width + 200, 100);
 
  add_static_box(group, -100, height, width + 200, 100);

  add_static_box(group, -100, -(height*(5-1)) , 100, height * 5);
  add_static_box(group, width, -(height*(5-1)) , 100, height * 5);
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

  int y = 50;
  const int num_links = stage->get_height() / 20 - 2;
  if((stage->get_width() / 20) < num_links)
    num_links = stage->get_width() / 20;

  Glib::RefPtr<Clutter::Rectangle> rect = Clutter::Rectangle::create();
  rect->set_size(18, 5);
  rect->set_position(stage->get_width() / 2, y);
  box2d->add_actor(rect);

  box2d->set_child_property(rect, "mode", (int)Clutter::Box2D::BOX2D_STATIC);  //TODO: Avoid the need for the int cast.

  Glib::RefPtr<Clutter::Actor> prev_actor = rect;

  for(int i = 0; i < num_links; ++i)
  {
    Glib::RefPtr<Clutter::Rectangle> box = Clutter::Rectangle::create();
    box->set_size(18, 5);
    box->set_position(20 + 20 * i, y+=1);
    box2d->add_actor(box);

    box2d->set_child_property(box, "manipulatable", true);
    box2d->set_child_property(box, "mode", (int)Clutter::Box2D::BOX2D_DYNAMIC);

    ClutterVertex anchor1 = { CLUTTER_UNITS_FROM_FLOAT (18), CLUTTER_UNITS_FROM_FLOAT (0.0) };
    ClutterVertex anchor2 = { CLUTTER_UNITS_FROM_FLOAT (0.0), CLUTTER_UNITS_FROM_FLOAT (0.0) };
    box2d->add_revolute_joint(prev_actor, box, &anchor1, &anchor2, 0.0);
   
    prev_actor = box;
  }

  box2d->set_simulating();

  stage->show();

  Clutter::main();

  return 0;
}
