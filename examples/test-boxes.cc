#include <cluttermm.h>
#include <cluttermm/init.h>
#include <clutter/clutter.h>

static bool
on_button_press_cb (ClutterButtonEvent *event, const Glib::RefPtr<Clutter::Stage>& stage)
{
  gint x, y;

  clutter_event_get_coords (reinterpret_cast<ClutterEvent*>(event), &x, &y);
  Glib::RefPtr<Clutter::Actor> rect = stage->get_actor_at_pos (x, y);
  if (!rect)
    return false;

  if (!Glib::RefPtr<Clutter::Rectangle>::cast_dynamic(rect))
    {
      g_print ("[!] No rectangle selected (%s selected instead)\n",
               g_type_name (G_OBJECT_TYPE (rect->gobj())));
      return false;
    }

  g_print ("[*] Picked rectangle at (%d, %d)\n", x, y);
  return false;
}

static bool
on_key_press_cb (ClutterKeyEvent *event)
{
  if (clutter_key_event_symbol (event) == CLUTTER_Escape)
    clutter_main_quit ();
  return true;
}

int
main (int argc, char *argv[])
{
    Glib::RefPtr<Clutter::Stage> stage;
    Glib::RefPtr<Clutter::VBox> vbox;
    Clutter::Color stage_color (0x00, 0x00, 0x00);
    Clutter::Color label_color (0xff, 0xff, 0xff, 0x99);
    gint i, j;

    Clutter::init (&argc, &argv);

    stage = Clutter::Stage::get_default ();
    stage->set_size (800, 600);
    stage->set_color (stage_color);

    stage->signal_button_press_event ().connect (
            sigc::bind(sigc::ptr_fun(&on_button_press_cb), stage));
    stage->signal_key_press_event ().connect (sigc::ptr_fun(&on_key_press_cb));

    vbox = Clutter::VBox::create ();

    vbox->set_default_padding (10, 0, 10, 0);
    vbox->set_position (100, 100);
    stage->add_actor (vbox);
    vbox->show ();

    for (i = 0; i < 3; i++)
    {
        Glib::RefPtr<Clutter::HBox> hbox = Clutter::HBox::create ();

        for (j = 0; j < 3; j++)
        {
            Glib::RefPtr<Clutter::Rectangle> rect;
            Clutter::Padding rect_padding;

            rect = Clutter::Rectangle::create (label_color);
            rect->set_size (100, 100);

            rect_padding.top = rect_padding.bottom = 0;
            rect_padding.left = CLUTTER_UNITS_FROM_INT (10);
            rect_padding.right = CLUTTER_UNITS_FROM_INT (10);

            hbox->pack (rect,
                    Clutter::PACK_START,
                    rect_padding);
            rect->show ();

            g_print ("rect[%d][%d] - (x:%3d, y:%3d, w:%3d, h:%3d)\n",
                    i, j,
                    rect->get_x (),
                    rect->get_y (),
                    rect->get_width (),
                    rect->get_height ());
        }

        vbox->pack (hbox);
        hbox->show ();

        g_print ("hbox[%d]    - (x:%3d, y:%3d, w:%3d, h:%3d)\n",
                i,
                hbox->get_x (),
                hbox->get_y (),
                hbox->get_width (),
                hbox->get_height ());

    }

    stage->show_all ();

    g_print ("vbox       - (x:%3d, y:%3d, w:%3d, h:%3d)\n",
            vbox->get_x (),
            vbox->get_y (),
            vbox->get_width (),
            vbox->get_height ());

    clutter_main ();

    return EXIT_SUCCESS;
}
