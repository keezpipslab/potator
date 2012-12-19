#import "EAGLView.h"
#include "Simulation.h"

@interface AppViewController : UIViewController {
	EAGLView* gl_view;
  Simulation* simulation;
}

- (id) initWithFrame:(CGRect) rect;
@end
