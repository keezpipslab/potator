#import "AppViewController.h"

@implementation AppViewController

- (id) initWithFrame:(CGRect) rect {
	self = [super init];
	if(self) {
		gl_view = [[EAGLView alloc] initWithFrame: rect];
		self.view = gl_view;
    simulation = [gl_view getSimulation];
	}
	return self;
}


- (void)viewDidLoad {
	[super viewDidLoad];
}

- (void) viewDidUnload {
	[super viewDidUnload];
}

- (void) viewWillAppear:(BOOL)animated {
	[super viewWillAppear:animated];
}

- (void) viewDidAppear:(BOOL)animated {
	[gl_view startAnimation];	
	[super viewDidAppear:animated];	
}

- (void) viewWillDisappear:(BOOL)animated {
	[super viewWillDisappear:animated];
}

- (void) viewDidDisappear:(BOOL)animated {
	[gl_view stopAnimation];	
	[super viewDidDisappear:animated];
}

- (void) touchesBegan:(NSSet*) touches withEvent:(UIEvent*) event {
	for(UITouch* t in touches) {
  	if([t tapCount] > 1) {
    	NSLog(@"Double tab!");
    	continue;
    }
		CGPoint loc = [t locationInView:self.view];  
    simulation->onTouchDown(loc.x, loc.y);
    //printf("%f, %f\n", loc.x, loc.y);
  }
}

- (void) touchesMoved: (NSSet*) touches withEvent:(UIEvent*) event {
	for(UITouch* t in touches) {
  	CGPoint loc = [t locationInView:self.view];
    simulation->onTouchMoved(loc.x, loc.y);
  }
}

- (void) touchesEnded: (NSSet*) touches withEvent:(UIEvent*) event {
	for(UITouch* t in touches) {
  	CGPoint loc = [t locationInView:self.view];
    simulation->onTouchUp(loc.x, loc.y);
  }
}

@end
