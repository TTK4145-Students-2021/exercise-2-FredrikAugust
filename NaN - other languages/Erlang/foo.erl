% Compile and run with `erlc foo.erl && erl -s foo start`

-module(foo).
-export([start/0]).

start() ->
	Ns = spawn(fun() -> number_server(17) end),
	spawn(fun() -> increment(Ns, 1000000) end),
	spawn(fun() -> decrement(Ns, 1000017) end),

	timer:sleep(2000),

	Ns ! {get_number, self()},
	receive
		Num -> 
			io:format("Number is: ~B~n", [Num])
	end,
	Ns ! exit.


increment(_Ns, 0) ->
	ok;
increment(Ns, TimesLeft) ->
	Ns ! increment_number,
	increment(Ns, TimesLeft-1).


decrement(_Ns, 0) ->
	ok;
decrement(Ns, TimesLeft) ->
	Ns ! decrement_number,
	decrement(Ns, TimesLeft-1).



number_server(Number) ->
	receive
		increment_number ->
			number_server(Number+1);
		decrement_number ->
			number_server(Number-1);
		{get_number, Caller} ->
			Caller ! Number,
			number_server(Number);
		exit ->
			ok
	end.

