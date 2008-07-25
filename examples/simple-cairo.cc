/* 
 * Pretty cairo flower hack.
 */

#include <clutter-cairomm.h>
#include <clutter/clutter.h>

int
main (int argc, char **argv)
{
  Clutter::Cairo::init (&argc, &argv);

  Glib::RefPtr<Clutter::Stage> stage = Clutter::Stage::get_default ();
  Clutter::Color stage_color (0x0, 0x0, 0x0, 0xff);
  stage->set_color (stage_color);

  guint size = stage->get_height () / 4;
  Glib::RefPtr<Clutter::Cairo::CairoTexture> circle =
      Clutter::Cairo::CairoTexture::create (size, size);
  // TODO: These brackets are necessary at the moment to limit the scope of the
  // Cairo::Context object.  Because of the way ClutterCairo is implemented,
  // whatever is drawn to the cairo context is not transferred to the Clutter
  // actor until the cairo context is destroyed.  So we need to force it to be
  // destroyed before we call clutter_main here
  {
      Cairo::RefPtr<Cairo::Context> cr = circle->create_cairo_context ();
      cr->set_operator (Cairo::OPERATOR_CLEAR);
      cr->paint ();
      cr->set_operator (Cairo::OPERATOR_OVER);
      cr->set_source_rgba (0.686, 0.96, 0.235, 0.8);
      cr->translate (size / 2, size / 2);
      cr->begin_new_path ();
      cr->arc (0.0,
              0.0,
              size / 2,
              0.0, 2 * M_PI);
      cr->fill ();
  }
  circle->set_position (stage->get_width () / 2 - size / 2,
                        stage->get_height () / 2 - size / 2);
  stage->add_actor (circle);

  stage->show_all ();
  stage->signal_key_press_event ().connect (sigc::hide (sigc::bind_return (sigc::ptr_fun (&clutter_main_quit), true)));

  Clutter::main();

  return 0;
}
