#include <cluttermm.h>
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

  Glib::RefPtr<Clutter::Stage> stage = Clutter::Stage::get_default ();
  stage->set_size(720, 576);
  stage->set_title("Box2D Test");

  Clutter::Color stage_color(0x00, 0x00, 0x00, 0x00);
  stage->set_color (stage_color);

  //TODO: Much. Use the class/slot structure from the gtkmm demo? murrayc.

  Clutter::main();

  return 0;
}
