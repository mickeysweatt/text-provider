# Architectural Overview:
----------------------
I have extensive component and class level doc but in general the architecture follows that have: a server, many types of caches, utilities, and text-provider.The utilities are generic tools that are independently useful separate from this task. The text-provider takes as a parameter a cache, that it will use it in its implementation. Every cache implements a common protocol, but the cache protocol is left sufficiently general to allow concrete implementations to make their own choice when it comes to caching decisions.

We server is built using Boost Asio, so every time a new request comes in the main thread accepts the request and creates a new session that then performs all the reads and writes necessary to process the request. Internally Boost Asio uses threading, selects, etc allowing the application to scale reasonably well. To add explicit threading support is something I considered, but chose to forgo as it increases the complexity of caching, because I would need to partition the space and should probably determine the first line a client will request to increase the probability of cache hits. Another option I considered here was to deploy a Memcached instance to act as a shared cache, but again this increased the complexity of the system significantly enough that other avenues seemed more fruitful given my limited time. Furthermore native C++ threads do no support a terminate call, it would make supporting he 'SHUTDOWN' command perhaps more difficult. Threading is the next thing I would experiment with if I were to spend more time on this assignment, and I attempted to build the architecture in a way to make this as feasible as possible.

An explanation of the performance of your system with 1GB, 10GB and 100GB input files.
--------------------------------------------------------------------------------------
The performance as of this service as the file size increases is mostly dependent on I/O, meaning that the main component implemented that will be affected by this would be caching. Another related aspect is the user(s) access patterns. Varying assumptions on these two options, in addition to the data set size itself, will affect how the this service performs.

* case 1 GB file:
	For a file of this size it is always optimal (assuming the user(s) request a significant number of lines) to use the optimistic-prefetch cache. This front loads the cost of loading the file, but assuming that the kernel also itself performs buffered I/O, this should not go to disc too many times for such a small file. This is the behavior my application will have for such a small file.

* case 10 GB file:
	In this case my application uses an LRU cache by default, but this is certainly configurable, and depending on the user(s) behavior other caches could be optimal. The default size for the LRU cache is ~7 GB, and assuming the probability of any line of the file is uniform (a arbitrary but I believe reasonable assumption to ease modeling), and assuming the number of requests is sufficiently large that the cache is full the majority of the time. The cache hit probability is ~.7, which considering we are assuming random access, and we have not sufficient space to cache the entire file is optimal. If we instead assume that most users read the file somewhat sequentially, even if we assume random starting points, and random ending points intuitively the cache hit rate should exceed .7, I suspect a rigorous argument would begin with my to modeling system this as a Markov Process (modeling the time in the system as an exponent distribution), which seems inappropriate for this assignment (a cursory search indicates that this http://www.ee.columbia.edu/~predrag/mypub/LRUsize04.pdf paper has the arguments I need).

* case 100 GB file:
	Again my application will use an LRU cache in this case, but at this size it does not seem it would yield much benefit. In fact unless we assume some subset of the file is more popular than another or that the cost of going to disk is more than two orders of magnitude worse than main memory, I would likely argue that the random access cache (which does not cache at all) would be optimal as the cache miss rate is likely high enough to make the cost of updating the cache more costly than it is worth. In the case that disk is prohibitively expensive, and the lines are sampled from a uniform, I would suggest using a different type of random cache that caches an arbitrary 7GB of lines to forgo the cost of evicting the cache so often.

# A discussion of what will happen if the # of client requests/second increases.
------------------------------------------------------------------------------- 
If the circumstance is that the client sends more request in a given second, if we assume a sufficiently small data set size (10 GB case above) the performance should scale well. One issue is that I chose to use synchronous reads and writes to ensure in order delivery meaning I cannot serve parallel requests from one client. The response delay will increase as miss rates increase, in the case of a hit the line is served from main memory and the delay should be reasonably low. One solution for this would be to change the writes to allow asynchronous delivery, meaning that in cases that the there is a cache miss we can still serve lines that are already in the cache. This would be implemented by changing he reads and writes I use to async reads and async writes. I chose the blocking implementation because the protocol specification was not sufficiently robust (no line or sequence numbers) to allow the client to be able to understand if they received asynchronous responses, which request this was to.

Another possibility for scaling, as my implementation does support an arbitrary number of clients, is that the number of clients increases. This will have a similar problem to the above in that I will have a bottleneck for cache misses. It is my understanding that due to its valuing consistency over raw throughput, Boost Asio will internally use a lock on the access to a shared variable, potentially causing all the requests to block on a cache miss in any of them (assuming all the requests are not rejected for being ill formed). Beyond the above solution, another improvement that could be made would be to change the caches to immediately return false upon cache miss, potentially dispatching the cache update request to a background thread. This would allow the system to increase throughput because the latency on for the missed thread is the same as before, we must read the missed line from the file, this however also allows the cache to be used by another request, which is unlikely to be also miss.

# What I Did Not Do That I Would Have Time To:
--------------------------------------------
o Component level testing of my modules (C++ native)
o Integration tests (python clients)
o Scaling tests (tsung)
o Better build system (autoconf, waf, etc)

# A list of external resources (blogs, websites, papers) you read when coming up with a solution to this exercise.
------------------------------------
* Extensive Stack Overflow, with credits given in the code for explicit code reuse
* Boost Asio tutorials and documentation

# A list of libs or other third party tools used by the system.
-------------------------------------------------------------
* Boost Asio
* Python 2 (for making little helper scripts)
* Command line tools

Time spent on this assignment.
~8 hours implementing
~3 documenting and styling (making the code more professional)
~1.5 composing this README
