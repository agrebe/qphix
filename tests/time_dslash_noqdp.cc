// $Id: t_dslash.cc,v 1.1 2008-08-26 13:24:29 bjoo Exp $

#include <iostream>
#include <cstdio>

using namespace std;
#include "qphix/qphix_config.h"
#include "qphix/print_utils.h"
#include "qphix/threadbind.h"

#ifdef QPHIX_QMP_COMMS
#include "qmp.h"
#endif

#include <omp.h>
#include "timeDslashNoQDP.h"

#include "cli_args.h"

int main(int argc, char **argv)
{
  // Initialize UnitTest jig
  processArgs(argc, argv);
  omp_set_num_threads(NCores_user * Sy_user * Sz_user);

#ifdef QPHIX_QMP_COMMS
  // Initialize QMP
  QMP_thread_level_t prv;
  if (QMP_init_msg_passing(&argc, &argv, QMP_THREAD_SINGLE, &prv) != QMP_SUCCESS) {
    QMP_error("Failed to initialize QMP\n");
    abort();
  }
  if (QMP_is_primary_node()) {
    printf("QMP IS INITIALIZED\n");
  }

  // Declare the logical topology
  if (QMP_declare_logical_topology(qmp_geometry, 4) != QMP_SUCCESS) {
    QMP_error("Failed to declare QMP Logical Topology\n");
    abort();
  }
#endif

  QPhiX::masterPrintf("Declared QMP Topology: %d %d %d %d\n",
                      qmp_geometry[0],
                      qmp_geometry[1],
                      qmp_geometry[2],
                      qmp_geometry[3]);

#ifdef QPHIX_QPX_SOURCE
  if (thread_bind) {
    QPhiX::setThreadAffinity(NCores_user, Sy_user * Sz_user);
  }
  QPhiX::reportAffinity();
#endif

  QPhiX::masterPrintf("Launching TestCase\n");

  // Launch the test case.
  timeDslashNoQDP test(By_user,
                       Bz_user,
                       NCores_user,
                       Sy_user,
                       Sz_user,
                       PadXY_user,
                       PadXYZ_user,
                       MinCt_user,
                       iters,
                       compress12,
                       prec_user,
                       do_dslash,
                       do_m,
                       do_cg,
                       do_bicgstab);

  test.run(nrow_in, qmp_geometry);
#ifdef QPHIX_QMP_COMMS
  QMP_finalize_msg_passing();
#endif
}
