
#include "gnuplot_interface.h"
#include <iostream>
#include <sstream>

using namespace std;

//#define DO_NOT_HAVE_GNUPLOT



// ---------------------------------------------------------
// Ref:
// http://user.frdm.info/ckhung/b/ma/gnuplot.php
// ---------------------------------------------------------

Gnuplot::Gnuplot():gnuplotpipe(0)
{
// with -persist option you will see the windows as your program ends
//gnuplotpipe=_popen("gnuplot -persist","w");
//without that option you will not see the window

// because I choose the terminal to output files so I don't want to see the window

#ifndef DO_NOT_HAVE_GNUPLOT
    gnuplotpipe=_popen("gnuplot","w");

    if (!gnuplotpipe)
    {
        cerr << ("Gnuplot not found !");
    }
#endif
}
// ---------------------------------------------------------
Gnuplot::~Gnuplot()
{
	if (!gnuplotpipe) return;

    fprintf(gnuplotpipe,"exit\n");
    _pclose(gnuplotpipe);
}
// ---------------------------------------------------------
void Gnuplot::operator()(const string & command)
{
	if (!gnuplotpipe) return;

    fprintf(gnuplotpipe,"%s\n",command.c_str());
    fflush(gnuplotpipe);
//    gnuplotpipe=_popen("gnuplot -persist","w");
// flush is necessary, nothing gets plotted else
}
// ---------------------------------------------------------
void Gnuplot::set_title(const std::string &title)
{
	ostringstream ss;
	ss << "set title \"" << title << "\"";
	operator()(ss.str());
}
// ---------------------------------------------------------
void Gnuplot::set_axis(const dimension d,const std::string &axisName)
{
	ostringstream ss;
	ss << "set ";
	if(d == dimension::X)
        ss << "x";
	if(d == dimension::Y)
        ss << "y";
	if(d == dimension::Z)
        ss << "z";
	ss <<"label '" << axisName << "'";
	operator()(ss.str());
}
// ---------------------------------------------------------
void Gnuplot::set_X_axis(const std::string &X_axis)
{
	ostringstream ss;
	ss << "set xlabel '" << X_axis << "'";
	operator()(ss.str());
}
// ---------------------------------------------------------
void Gnuplot::set_Y_axis(const std::string &Y_axis)
{
	ostringstream ss;
	ss << "set ylabel '" << Y_axis << "'";
	operator()(ss.str());
}
// ---------------------------------------------------------
void Gnuplot::set_xrange(int BEGIN, int END)
{
	ostringstream ss;

	ss << "set xrange [" << BEGIN << ":" << END << "] " <<  ";" ;
	operator()(ss.str());
}
// ---------------------------------------------------------
void Gnuplot::set_yrange(int BEGIN, int END)
{
	ostringstream ss;

	ss << "set yrange [" << BEGIN << ":" << END << "] " <<  ";" ;
	operator()(ss.str());
}
// ---------------------------------------------------------
void Gnuplot::plot(const std::string &fname, std::size_t x, std::size_t y)
{
	ostringstream ss;

	ss << "plot \"" << fname << "\" using " << x << ":" << y;
	operator()(ss.str());
}
// ---------------------------------------------------------
void Gnuplot::plot(const std::string &fname,const std::string &tittle)
{
	ostringstream ss;

	ss << "plot " << fname << " title \"" << tittle << "\"" <<";" ;
	operator()(ss.str());
}
// ---------------------------------------------------------
void Gnuplot::plot(const std::string &fnameWithTittle)
{
	ostringstream ss;

	ss << "plot " << fnameWithTittle <<";" ;
	operator()(ss.str());
}
// ---------------------------------------------------------
void Gnuplot::splot(const std::string &fname, std::size_t x, std::size_t y, std::size_t z)
{
	ostringstream ss;

	ss << "splot \"" << fname << "\" using " << x << ":" << y << ":" << z;
	operator()(ss.str());
}
// ---------------------------------------------------------
