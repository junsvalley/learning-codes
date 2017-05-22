-module(study).
-vsn(v1).
-author([gufeng, tom]).
-purpose("study records").
%%-export([qsort/1, cost/1, total2/1, split_odds_evens/1]).
%%-export([total/1, sum/1, for/3, filter/2, catcher/1, catcher2/0]).
-compile(export_all).
-import(lists, [map/2]).
-include("study.hrl").


cost(oranges)   -> 5;
cost(newspaper) -> 1;
cost(apples)    -> 8;
cost(pears)     -> 4;
cost(milk)      -> 6.

total ([{What, N}|T]) -> shop:cost(What) * N + total(T);
total ([])            -> 0.

sum([H|T], N) -> sum(T, H+N);
sum([], N) -> N.

sum(L) -> sum(L, 0).

for(Max, Max, F) -> [F(Max)];
for(I, Max, F) -> [F(I)|for(I+1, Max, F)].

total2 (L) -> sum(map(fun({What, N}) -> cost(What) * N end, L)).

qsort([Pivot|T]) ->
	qsort([X || X <- T, X < Pivot])
	++ [Pivot] ++
	qsort([X || X <- T, X >= Pivot]);
qsort([])        -> [].

filter(P, [H|T]) ->
	case P(H) of
		true  -> [H | filter(P, T)];
		false -> filter(P, T)
	end;
filter(_, [])    -> [].

odds_and_evens_acc([H|T], O, E) ->
	case ( H rem 2 ) of
		1 -> odds_and_evens_acc(T, [H | O], E);
		0 -> odds_and_evens_acc(T, O, [H | E])
	end;
odds_and_evens_acc([], O, E) -> {lists:reverse(O), lists:reverse(E)}.

split_odds_evens(L) -> odds_and_evens_acc(L, [], []).

generate_exception(1) -> a;
generate_exception(2) -> throw(a);
generate_exception(3) -> exit(a);
generate_exception(4) -> erlang:error(a);
generate_exception(5) -> {'EXIT', a}.

catcher(N) ->
	try generate_exception(N) of
		Val -> {N, normal, Val}
	catch
		throw:X -> {N, caught, thrown, X, erlang:get_stacktrace()};
		exit:X -> {N, caught, exited, X};
		error:X -> {N, caught, error, X}
	end.

catcher2() -> [ catch generate_exception(I) || I <- [1,2,3,4,5]].

lookup(K, [H|T]) ->
	case H of
		{K, V} -> {ok, V};
		_ -> lookup(K, T)
	end;
lookup(_, []) -> error.

attribute(F, K) ->
	case beam_lib:chunks(F, [attributes]) of 
		{ok, {_, [{attributes, L}]}} ->
			case lookup(K, L) of
				{ok, Val} -> Val;
				error  -> ?TRACE("Can not found"), exit("Can not found")
			end;
		_ ->
			exit(badFile)
	end.

%%number < atom < reference < fun < port < pid < tuple < list < bit string
%%
%%
