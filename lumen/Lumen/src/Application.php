<?php

namespace Lumen;

use Illuminate\Http\Request;
use Illuminate\Container\Container;
use Symfony\Component\HttpFoundation\Request as SymfonyRequest;

class Application extends Container
{
    use Concerns\RoutesRequests;

    /**
     * Prepare the given request instance for use with the application.
     *
     * @param  \Symfony\Component\HttpFoundation\Request $request
     * @return \Illuminate\Http\Request
     */
    protected function prepareRequest(SymfonyRequest $request)
    {
        if (!$request instanceof Request) {
            $request = Request::createFromBase($request);
        }

        $request->setUserResolver(function ($guard = null) {
            return $this->make('auth')->guard($guard)->user();
        })->setRouteResolver(function () {
            return $this->currentRoute;
        });

        return $request;
    }
}
