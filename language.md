<!--
In Exercise 3 & 4 (Network exercises) and the project, you will be using a language of your own choice. You are of course free to change your mind at any time, but to help avoid this situation (and all its associated costs) it is worth doing some research already now.

Here are a few things you should consider:

Think about how want to move data around (reading buttons, network, setting motor & lights, state machines, etc). Do you think in a shared-variable way or a message-passing way? Will you be using concurrency at all?
How will you split into modules? Functions, objects, threads? Think about what modules you need, and how they need to interact. This is an iterative design process that will take you many tries to get "right".
The networking part is often difficult. Can you find anything useful in the standard libraries, or other libraries?
While working on new sections on the project you'll want to avoid introducing bugs to the parts that already work properly. Does the language have a framework for making and running tests, or can you create one? Testing multithreaded code is especially difficult.
Code analysis/debugging/IDE support?
Create a new file with some reflections on language choice (somewhere in the 100-300 words range (-ish)), and push it to GitHub. We don't expect a full design, just some preliminary thoughts and ideas, all subject to change as you learn more.
-->

I will use _Erlang_.

- Everything will be split into modules and functions -- it's a functional language so there's really no other option.
- Communication will be handled by the OTP pattern with `call` and `cast` to handle function calls that require a return value, and those who _only_ dispatch an action.
Due to the internals of erlang and OTP communication between threads on our machine and other computers is mostly the same, removing the need for complex data passing over networks.
- You can run test suites in erlang; http://erlang.org/doc/apps/eunit/chapter.html. With a modular design we can test the "callbacks" of the otp casts/calls easily and ensure our business logic is sound.
- Code analysis and IDE support isn't the best for erlang, but it's a very mature language so there are tools available. Personally I write my erlang code in Vim.