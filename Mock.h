@interface Mock : NSObject
{
}
-(void)loadedData:(NSDictionary*)data;
-(void)displayData:(id)data;
@end

@implementation Mock
- (id)init
{
	if((self = [super init]))
	{
	}
	return self;
}

-(void)loadedData:(NSDictionary*)data
{
	[self displayData:data];
	
}

-(void)displayData:(id)data
{
	NSDictionary *feedItems = [data objectForKey:@"feedItems"];
	NSLog(@"Data loaded to delegate. Containing %d items", [feedItems count]);
	for (id item in feedItems) {
		NSLog(@"title: %@",[item objectForKey:@"title"]);
	}
}

@end
