-record(records, { key1 = default1, key2 = deafult2 }).

-ifdef(debug).
-define(TRACE(X), io:format("[~s]<~s>:~B\t ~s~n", [?MODULE, ?FILE, ?LINE, X])).
-else.
-define(TRACE(X), void).
-endif.
