#ifndef GTK_FILE_VIEWER_FRONTEND
#define GTK_FILE_VIEWER_FRONTEND
#include <c_minilib_error.h>
#include <stdint.h>

/******************************************************************************
 *                                Frontend                                    *
 ******************************************************************************/
typedef struct Frontend *frontend_t;

cme_error_t frontend_create(const char *app_name, const char *window_name,
                            int32_t window_x, int32_t window_y,
                            frontend_t *out);

void frontend_destroy(frontend_t *out);
cme_error_t frontend_start(frontend_t frontend);
#endif // GTK_FILE_VIEWER_FRONTEND
