/* 
 * Pretty cairo flower hack.
 * This is a very cursory translation from C to C++.  As such, you will notice
 * that there are a lot of C-isms in this example yet, but it should still give
 * an idea of how to use cluttermm-cairo
 *
 * I C++ified this a bit. armin.
 */

#include <clutter-cairomm.h>
#include <cluttermm.h>

#include <cstdlib>
#include <ctime>

#define PETAL_MIN 20
#define PETAL_VAR 40
#define N_FLOWERS 40 /* reduce if you have a small card */

struct Flower : public Clutter::Cairo::CairoTexture
{
    static Glib::RefPtr<Flower> create ()
    {
        gint size;
        gint petal_size; 
        petal_size = PETAL_MIN + std::rand() % PETAL_VAR;
        size = petal_size * 8;

        return Glib::RefPtr<Flower> (new Flower (size));

        petal_size -= std::rand() % (size/8);
    }

    Flower (guint size) :
        CairoTexture (size, size)
    {
        gint i, j;

        const double colors[] = {
            0.71, 0.81, 0.83,
            1.0,  0.78, 0.57,
            0.64, 0.30, 0.35,
            0.73, 0.40, 0.39,
            0.91, 0.56, 0.64,
            0.70, 0.47, 0.45,
            0.92, 0.75, 0.60,
            0.82, 0.86, 0.85,
            0.51, 0.56, 0.67,
            1.0, 0.79, 0.58,

        };
        gint n_groups;    /* Num groups of petals 1-3 */
        gint n_petals;    /* num of petals 4 - 8  */
        gint pm1, pm2;

        gint idx, last_idx = -1;

        n_groups = std::rand() % 3 + 1;

        gint petal_size = size / 8; 
        Cairo::RefPtr<Cairo::Context> cr = create_cairo_context ();

        cr->set_tolerance (0.1);

        /* Clear */
        cr->set_operator (Cairo::OPERATOR_CLEAR);
        cr->paint();
        cr->set_operator (Cairo::OPERATOR_OVER);

        cr->translate(size/2, size/2);

        for (i=0; i<n_groups; i++)
        {
            n_petals = std::rand() % 5 + 4;
            cr->save ();

            cr->rotate (std::rand() % 6);

            do {
                idx = (std::rand() % (sizeof (colors) / sizeof (double) / 3)) * 3;
            } while (idx == last_idx);

            cr->set_source_rgba (colors[idx], colors[idx+1],
                    colors[idx+2], 0.5);

            last_idx = idx;

            /* some bezier randomness */
            pm1 = std::rand() % 20;
            pm2 = std::rand() % 4;

            for (j=1; j<n_petals+1; j++)
            {
                cr->save ();
                cr->rotate (((2*M_PI)/n_petals)*j);

                /* Petals are made up beziers */
                cr->begin_new_path ();
                cr->move_to (0, 0);
                cr->rel_curve_to (petal_size, petal_size,
                                  (pm2+2)*petal_size, petal_size,
                                  (2*petal_size) + pm1, 0);
                cr->rel_curve_to (0 + (pm2*petal_size), -petal_size,
                                  -petal_size, -petal_size,
                                  -((2*petal_size) + pm1), 0);
                cr->close_path ();
                cr->fill ();
                cr->restore ();
            }

            cr->restore ();
        }

        /* Finally draw flower center */
        do {
            idx = (std::rand() % (sizeof (colors) / sizeof (double) / 3)) * 3;
        } while (idx == last_idx);

        if (petal_size < 0)
            petal_size = std::rand() % 10;

        cr->set_source_rgba (colors[idx], colors[idx+1], colors[idx+2], 0.5);

        cr->arc(0, 0, petal_size, 0, M_PI * 2);
        cr->fill();
    }

    gint x,y,rot,v,rv;
};

bool
tick (const std::vector<Glib::RefPtr<Flower> >& flowers)
{
    gint i = 0;

    for (std::vector<Glib::RefPtr<Flower> >::const_iterator iter = flowers.begin(); iter != flowers.end(); ++ iter)
    {
        Glib::RefPtr<Flower> flower = *iter;
        flower->y   += flower->v;
        flower->rot += flower->rv;

        if (flower->y > (gint) Clutter::Stage::get_default ()->get_height ())
            flower->y = -flower->get_height ();

        flower->set_position (flower->x, flower->y);

        flower->set_rotation (Clutter::Z_AXIS,
                flower->rot,
                flower->get_width ()/2,
                flower->get_height ()/2,
                0);
    }

    return true;
}

int
main (int argc, char **argv)
{
  int              i;
  Glib::RefPtr<Clutter::Stage> stage;
  Clutter::Color stage_color (0x0, 0x0, 0x0, 0xff);
  std::vector<Glib::RefPtr<Flower> > flowers;

  std::srand(std::time(NULL));

  Clutter::Cairo::init (&argc, &argv);

  stage = Clutter::Stage::get_default ();

  stage->set_color (stage_color);

  stage->fullscreen ();

  flowers.reserve(N_FLOWERS);
  for (i=0; i< N_FLOWERS; i++)
    {
      Glib::RefPtr<Flower> flower = Flower::create();
      flower->x   = std::rand() % stage->get_width() - (PETAL_MIN+PETAL_VAR)*2;
      flower->y   = std::rand() % stage->get_height();
      flower->rv  = std::rand() % 5 + 1;
      flower->v   = std::rand() % 10 + 2;

      stage->add_actor (flower);
      flower->set_position (flower->x, flower->y);
      flowers.push_back(flower);
    }

  Clutter::frame_source_add (sigc::bind (sigc::ptr_fun (&tick), sigc::ref(flowers)), 50);
  //Glib::signal_timeout ().connect (sigc::bind (sigc::ptr_fun (&tick), sigc::ref(flowers)), 50);

  stage->show_all ();
  stage->signal_key_press_event ().connect (sigc::hide (sigc::bind_return (sigc::ptr_fun (&Clutter::main_quit), true)));

  Clutter::main();

  return 0;
}
