#import "CJSONDeserializer.h"
@interface CocoaParty : NSObject {
	NSString *baseURI;
	NSString *requestPath;
	NSMutableData *requestedJSONData;
	id *loadedDelegate;
}
	@property (nonatomic,retain) NSString *baseURI;
	@property (nonatomic,retain) NSString *requestPath;
	@property (nonatomic,retain) NSMutableData *requestedJSONData;
	@property (nonatomic,retain) id *loadedDelegate;
	
	- (id)getWithPath:(NSString *)path andParams:(NSDictionary *)params withDelegate:(id)delegate loadedSelector:(SEL)selector;
	-	(id)formatQueryString:(NSDictionary*)params;
	-	(id)formatUrl;
	-	(id)doRequestForUrl:(NSString*)url;
	- (id)parseJSON:(NSMutableData *)data;
	- (id)initWithHost:(NSString *)host;
	
@end

@implementation CocoaParty

	@synthesize baseURI;
	@synthesize requestPath;
	@synthesize requestedJSONData;
	@synthesize loadedDelegate;

	- (id)initWithHost:(NSString*)host
	{
		if((self = [super init])) {
			self.baseURI  = host;
		}
		return self;
	}
	
	-	(id)doRequestForUrl:(NSString*)url
	{
		NSURL *requestUrl 		= [NSURL URLWithString:url];
		NSURLRequest *request = [NSURLRequest requestWithURL:requestUrl 
																					cachePolicy:(NSURLRequestCachePolicy)nil 
																					timeoutInterval:(NSTimeInterval)10];
		requestedJSONData 		= [[NSMutableData data] retain];
		[NSURLConnection connectionWithRequest:request 
										 delegate:self ];
		[requestUrl release];
		return nil;
	}
	
	- (id)getWithPath:(NSString *)path 
				andParams:(NSDictionary *)params 
				withDelegate:(id)delegate 
				loadedSelector:(SEL)selector
	{
		self.requestPath 		= path;
		self.loadedDelegate = delegate;
		
		NSString* url 			= [[NSString alloc] initWithFormat:@"%@%@",[self formatUrl],[self formatQueryString:params]];
		NSLog(@"requesting :: %@",url);
		[self doRequestForUrl:url];
		
		NSLog(@"Delegating to:: %@ ",self.loadedDelegate);
		[url release];
		return nil;
	}
	
	- (id)parseJSON:(NSMutableData *)data {
		NSLog(@"Parsing JSON");
		NSError *error 					 = nil;
		NSDictionary *dictionary = [[CJSONDeserializer deserializer] 
															   deserializeAsDictionary:data error:&error];
		return dictionary;
	}
	
	-	(id)formatUrl{
		NSString *url = [[NSString alloc] initWithFormat:@"%@%@?",[self baseURI],[self requestPath],@"?"];
		NSLog(@"url :: %@",url);
		return url;
	}
	
	-	(id)formatQueryString:(NSDictionary*)params
	{
		NSString *str = [[NSString alloc] init];
		for (id key in params) {
			str = [str stringByAppendingFormat:@"%@=%@&", key, [params objectForKey:key]];
		}
		
		[params release];
		NSLog(@"query :: %@",str);
		return str;
	}
		
	// NSURLConnection Delegate Methods //
	- (void)connection:(NSURLConnection *)connection didReceiveData:(NSMutableData *)data {
		NSLog(@"Recieving Data...");
		[requestedJSONData appendData:data];
	}
	- (void)connectionDidFinishLoading:(NSURLConnection *)connection {
		NSLog(@"Fininshed Loading...");
		NSDictionary * jsonDictionary = [self parseJSON:requestedJSONData];
		(void) [self.loadedDelegate performSelector:@selector(loadedData:)
												        withObject:jsonDictionary];
	}
	- (void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error{
		NSLog(@"Connection Error ::", error);
	}
	// ----------------------------- //

@end
	
