// Copyright (c) 1994 Darren Vengroff
//
// File: test_ami_arith.cpp
// Author: Darren Vengroff <darrenv@eecs.umich.edu>
// Created: 12/10/94
//

#include <portability.h>

#include <versions.h>
VERSION(test_ami_arith_cpp,"$Id: test_ami_arith.cpp,v 1.11 2004-08-12 15:15:11 jan Exp $");

#include "app_config.h"        
#include "parse_args.h"

// Get AMI_scan().
#include <ami_scan.h>

// Get utitlities for ascii output.
#include <ami_scan_utils.h>

// Get some scanners.
#include "scan_square.h"
#include "scan_count.h"

// Get stream arithmetic.
#include <ami_stream_arith.h>

static char def_crf[] = "osc.txt";
static char def_irf[] = "osi.txt";
static char def_frf[] = "osf.txt";

static char *count_results_filename = def_crf;
static char *intermediate_results_filename = def_irf;
static char *final_results_filename = def_frf;

static bool report_results_count = false;
static bool report_results_intermediate = false;
static bool report_results_final = false;

static const char as_opts[] = "C:I:F:cif";
void parse_app_opt(char c, char *optarg)
{
    switch (c) {
        case 'C':
            count_results_filename = optarg;
        case 'c':
            report_results_count = true;
            break;
        case 'I':
            intermediate_results_filename = optarg;
        case 'i':
            report_results_intermediate = true;
            break;
        case 'F':
            final_results_filename = optarg;
        case 'f':
            report_results_final = true;
            break;
    }
}


int main(int argc, char **argv)
{
    AMI_err ae;

    parse_args(argc,argv,as_opts,parse_app_opt);

    if (verbose) {
      cout << "test_size = " << test_size << "." << endl;
        cout << "test_mm_size = " << static_cast<TPIE_OS_OUTPUT_SIZE_T>(test_mm_size) << "." << endl;
        cout << "random_seed = " << random_seed << "." << endl;
    } else {
        cout << test_size << ' ' << static_cast<TPIE_OS_OUTPUT_SIZE_T>(test_mm_size) << ' ' << random_seed;
    }
    
    // Set the amount of main memory:
    MM_manager.set_memory_limit (test_mm_size);
        
    AMI_STREAM<int> amis0;
    AMI_STREAM<int> amis1;
    AMI_STREAM<int> amis2;

    // Streams for reporting values to ascii streams.
    
    ofstream *osc;
    ofstream *osi;
    ofstream *osf;
    cxx_ostream_scan<int> *rptc = NULL;
    cxx_ostream_scan<int> *rpti = NULL;
    cxx_ostream_scan<int> *rptf = NULL;
    
    if (report_results_count) {
        osc = new ofstream(count_results_filename);
        rptc = new cxx_ostream_scan<int>(osc);
    }
    
    if (report_results_intermediate) {
        osi = new ofstream(intermediate_results_filename);
        rpti = new cxx_ostream_scan<int>(osi);
    }
    
    if (report_results_final) {
        osf = new ofstream(final_results_filename);
        rptf = new cxx_ostream_scan<int>(osf);
    }
    
    // Write some ints.
    scan_count sc(test_size);

    ae = AMI_scan(&sc, &amis0);

    if (verbose) {
      cout << "Wrote the initial sequence of values." << endl;
        cout << "Stopped (didn't write) with ii = "
             << sc.ii << ". operate() called " 
	     << sc.called << " times." << endl;
        cout << "Stream length = " << amis0.stream_len() << endl;
    }

    if (report_results_count) {
        ae = AMI_scan(&amis0, rptc);
    }
    
    // Square them.
    scan_square<int> ss;
        
    ae = AMI_scan(&amis0, &ss, &amis1);

    if (verbose) {
        cout << "Squared them; last squared was ii = "
             << ss.ii << ". operate() called " 
	     << ss.called << " times." << endl;
        cout << "Stream length = " << amis1.stream_len() << endl;
    }
    
    AMI_scan_div<int> sd;
    
    ae = AMI_scan(&amis1, &amis0, &sd, &amis2);
        
    if (verbose) {
      cout << "Divided them." << endl
	   << "Stream length = " << amis2.stream_len() << endl;
    }
    
    if (report_results_final) {
        ae = AMI_scan(&amis2, rptf);
    }
    
    return 0;
}