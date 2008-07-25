#include <cluttermm.h>
#include <iostream>

namespace
{

const unsigned int TRAILS = 0;
const unsigned int N_ACTORS = 6;

unsigned int get_radius(unsigned int num_actors)
{
    return (Clutter::Stage::get_default()->get_height()
            + Clutter::Stage::get_default()->get_height()) / num_actors;
}

struct SuperOH
{
    std::vector<Glib::RefPtr<Clutter::Actor> > hands;
    Glib::RefPtr<Clutter::Actor> bgtex;
    Glib::RefPtr<Clutter::Group> group;
};

bool on_button_press (Clutter::ButtonEvent *event, const Glib::RefPtr<Clutter::Stage>& stage)
{
    g_print ("*** button press event (button:%d) ***\n",
            event->button);

    Glib::RefPtr<Clutter::Actor> e = stage->get_actor_at_pos(event->x, event->y);
    if(e) e->hide();

    return false;
}

bool on_key_release (Clutter::KeyEvent *event)
{
    g_print ("*** key press event (key:%c) ***\n",
            Clutter::key_event_symbol(event));

    if(Clutter::key_event_symbol(event) == CLUTTER_q)
        Clutter::main_quit();

    return false;
}

// Timeline handler
void on_new_frame (int frame_num, SuperOH* oh)
{
    // Rotate everything clockwise about stage center
    oh->group->set_rotation (Clutter::Z_AXIS,
                             frame_num,
                             Clutter::Stage::get_default ()->get_width () / 2,
                             Clutter::Stage::get_default ()->get_height () / 2,
                             0);

    for (unsigned int i = 0; i < oh->hands.size(); i++)
    {
        double scale_x, scale_y;

        oh->hands[i]->get_scale (scale_x, scale_y);

        /* Rotate each hand around their centers - to get this we need
         * to take into account any scaling.
         *
         * FIXME: scaling causes drift so disabled for now. Need rotation
         * unit based functions to fix.
         */
        oh->hands[i]->set_rotation (Clutter::Z_AXIS,
                                  - 6.0 * frame_num, 0, 0, 0);
    }
}

} // anonymous namespace

int main(int argc, char *argv[])
{
    Glib::OptionEntry entry;
    entry.set_short_name('n');
    entry.set_long_name("num-actors");
    entry.set_description("Number of actors");
    entry.set_arg_description("ACTORS");

    Glib::OptionGroup group("actor", "Specifies actor properties");
    int num_actors = N_ACTORS;
    group.add_entry(entry, num_actors);

    Glib::OptionContext context;
    context.set_main_group(group);

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

    Clutter::Color stage_color (0x61, 0x64, 0x8c, 0xff);
    Glib::RefPtr<Clutter::Stage> stage = Clutter::Stage::get_default ();
    stage->set_size (800, 600);

    stage->set_title ("Actors Test");
    stage->set_color (stage_color);

    SuperOH oh;

    // Create a timeline to manage animation
    Glib::RefPtr<Clutter::Timeline> timeline =
        Clutter::Timeline::create (360, 60); // num frames, fps
    timeline->set_loop (true); // have it loop

    // fire a callback for frame change
    timeline->signal_new_frame ().connect
        (sigc::bind (sigc::ptr_fun(on_new_frame), &oh));

    // TODO: these next 3 objects are not currently used in the example, but
    // they cause problems on application exit.  If they are commented out, the
    // program runs and exits without problems.  There seems to be some sort of
    // reference-counting issue
    // Perhaps that's clutter bug #856.

    // Set up some behaviours to handle scaling
    Glib::RefPtr<Clutter::Alpha> alpha =
        Clutter::Alpha::create (timeline, Clutter::ALPHA_SINE);

    Glib::RefPtr<Clutter::BehaviourScale> scaler_1 =
        Clutter::BehaviourScale::create (alpha,
                0.5, 0.5,
                1.0, 1.0);

    Glib::RefPtr<Clutter::BehaviourScale> scaler_2 =
        Clutter::BehaviourScale::create (alpha,
                1.0, 1.0,
                0.5, 0.5);

    // create a new group to hold multiple actors in a group
    oh.group = Clutter::Group::create();

    oh.hands.reserve(num_actors);
    for (int i = 0; i < num_actors; i++)
    {
        gint x, y, w, h;
        gint radius = get_radius(num_actors);

        // Create a texture from file, then clone it to save resources
        if (i == 0)
        {
	    try
	    {
                Glib::RefPtr<Clutter::Texture> texture(Clutter::Texture::create());
                texture->set_from_file("actor.png");
                oh.hands.push_back (texture);
            }
            catch(const Glib::Exception& ex)
            {
                std::cerr << "Could not load texture: " << ex.what() << std::endl;
		return -1;
            }
        }
        else
        {
            oh.hands.push_back(Clutter::CloneTexture::create
                    (Glib::RefPtr<Clutter::Texture>::cast_dynamic
                     (oh.hands[0])));
        }

        // Place around a circle
        w = oh.hands[0]->get_width ();
        h = oh.hands[0]->get_height ();

        x = Clutter::Stage::get_default ()->get_width () / 2 
            + radius
            * cos (i * M_PI / (num_actors / 2))
            - w / 2;
        y = Clutter::Stage::get_default ()->get_height () / 2 
            + radius
            * sin (i * M_PI / (num_actors / 2))
            - h / 2;

        oh.hands[i]->set_position (x, y);
	oh.hands[i]->move_anchor_point_from_gravity(Clutter::GRAVITY_CENTER);

        // Add to our group group
        oh.group->add_actor(oh.hands[i]);

#if 1 /* FIXME: disabled as causes drift - see comment above */
        if (i % 2)
            scaler_1->apply (oh.hands[i]);
        else
            scaler_2->apply (oh.hands[i]);
#endif
    }

    oh.group->show_all ();

    // Add the group to the stage
    stage->add_actor (oh.group);

    // Show everying ( and map window )
    stage->show_all ();

    stage->signal_button_press_event ().connect (sigc::bind (sigc::ptr_fun
                (on_button_press), stage));

    stage->signal_key_release_event ().connect (sigc::ptr_fun(on_key_release));

    // and start it
    timeline->start ();

    // TODO: wrap clutter_main ?
    Clutter::main();

    return 0;
}
