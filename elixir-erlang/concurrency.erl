-module(concurrency).
-export([start/0, start/2, max/1, tick/2, stop/0, timer/2]).

rcv() ->
        receive
                {From, {rectangle, W, H}} ->
                        io:format("[~p] Area of rectangle is ~p~n", [self(), W*H]),
			From ! {self(), W*H},
                        rcv();
                {From, {circle, R}} ->
                        io:format("[~p] Area of circle is ~p~n", [self(), 3.14159*R*R]),
			From ! {self(), 3.14159*R*R},
                        rcv();
                {From, Other} ->
                        io:format("[~p] unknow ~p~n", [self(), Other]),
			From ! {self(), "unknow geometry"},
                        rcv()
        end.

rpc(P, M) ->
	P ! {self(), M},
	receive
		{P, Res} ->
			io:format("[~p] area is ~p~n", [self(), Res])
	end.

start() ->
	P = spawn(fun rcv/0),
	rpc(P, {rectangle, 3, 4}),
	rpc(P, {circle, 3}),
	rpc(P, {triangle, 3, 4}).

wait() ->
	receive
		die -> void
	end.

for(N, N, F) -> [F()];
for(I, N, F) -> [F() | for(I+1, N, F)].

max(N) ->
	M = erlang:system_info(process_limit),
	io:format("Maximum allowed proceses:~p~n", [M]),
	statistics(runtime),
	statistics(wall_clock),
	L = for(1, N,
		 fun() -> 
			spawn(fun() -> wait() end)
		 end
	),
	{_, T1} = statistics(runtime),
	{_, T2} = statistics(wall_clock),
	lists:foreach(fun(P) -> P ! die end, L),
	U1 = T1 * 1000 / N,
	U2 = T2 * 1000 / N,
	io:format("Process spawn time=~p (~p) microseconds~n", [U1, U2]).


tick(T, F) ->
	receive
		stop -> void
	after T * 1000 -> %%seconds
		F(),
		tick(T, F)
	end.

stop() ->
	clock ! stop.

timer(T, F) ->
	register(clock, spawn(fun() -> tick(T, F) end)).


start(A, [T, F]) ->
	register(A, spawn_link(concurrency, fun tick/2, [T, F])).
	%%register(A, spawn(concurrency, tick, [T, F])).
	%%

%%run(M, N) ->
%%	L = for(1, N, fun() -> spawn(fun rcv/0) end)
