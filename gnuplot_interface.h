#include <string>
#include <stdio.h>

#include <string>
#include <cstddef>

// ----------------------------------------------------------------------
// Gnuplot
//
// This is just a very simple interface to call gnuplot in the program.
// Now it seems to work only under windows + visual studio.
// ----------------------------------------------------------------------

enum dimension{X = 0,Y,Z};

class Gnuplot
{
public:
    Gnuplot() ;
    ~Gnuplot();

	// prohibit copying (VS2012 does not support 'delete')
	Gnuplot(const Gnuplot &);
	Gnuplot & operator=(const Gnuplot &);

	// send any command to gnuplot
	void operator ()(const std::string & command);

	void reset() { operator()("reset"); }
	void replot() { operator()("replot"); }
	void set_title(const std::string &title);
	void set_axis(const dimension d,const std::string &axisName);
	void set_X_axis(const std::string &X_axis);
	void set_Y_axis(const std::string &Y_axis);

	void set_xrange(int BEGIN, int END);
	void set_yrange(int BEGIN, int END);

	void plot(const std::string &fname, std::size_t x, std::size_t y);
	void plot(const std::string &fname,const std::string &tittle);
	void plot(const std::string &fnameWithTittle);
    void splot(const std::string &fname, std::size_t x, std::size_t y, std::size_t z);

protected:
    FILE *gnuplotpipe;
};
