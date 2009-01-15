//
//  main.m
//  CocoaParty
//
//  Created by Christopher Burnett on 1/15/09.
//  Copyright Digital Scientists 2009. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "CocoaParty.h"
#import "Mock.h"
int main(int argc, char *argv[])
{
	
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	Mock *myObject = [[Mock alloc] init];
	
	CocoaParty *cocoaParty   	= [[CocoaParty alloc] initWithHost:@"http://missionzero.org"];
	NSDictionary *params 			= [NSDictionary dictionaryWithObjectsAndKeys:
		@"foo", @"query", 
		@"name", @"sort_by", 
	nil];
	
	[cocoaParty getWithPath:@"/widgets/feed/" 
							andParams:params 
							withDelegate:myObject 
							loadedSelector:@selector(loadedData:)];
	
	[cocoaParty release];
	[myObject release];
	
	return NSApplicationMain(argc,  (const char **) argv);
	[pool drain];
}
