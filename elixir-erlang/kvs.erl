-module(kvs).

-export([start/0, store/2, lookup/1]).

start() -> register(kvs, spawn(fun() -> loop() end)).

store(K, V) -> rpc({store, K, V}).

lookup(K) -> rpc({lookup, K}).

rpc(Q) ->
	kvs ! {self(), Q},
	receive
		{kvs, R} -> R
	end.

loop() ->
	receive
		{From, {store, K, V}} ->
			put(K, {ok, V}),
			From ! {kvs, true},
			loop();
		{From, {lookup, K}} ->
			From ! {kvs, get(K)},
			loop()
	end.
