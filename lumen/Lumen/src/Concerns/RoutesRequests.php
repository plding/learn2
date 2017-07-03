<?php

namespace Lumen\Concerns;

use Closure;
use Illuminate\Http\Request;
use Lumen\Routing\Closure as RoutingClosure;
use Psr\Http\Message\ResponseInterface as PsrResponseInterface;
use Symfony\Component\HttpFoundation\Request as SymfonyRequest;
use Symfony\Bridge\PsrHttpMessage\Factory\HttpFoundationFactory;
use Symfony\Component\HttpFoundation\Response as SymfonyResponse;

trait RoutesRequests
{
    /**
     * All of the routes waiting to be registered.
     *
     * @var array
     */
    protected $routes = [];

    /**
     * All of the global middleware for the application.
     *
     * @var array
     */
    protected $middleware = [];

    /**
     * Register a route with the application.
     *
     * @param  string  $uri
     * @param  mixed  $action
     * @return $this
     */
    public function get($uri, $action)
    {
        $this->addRoute('GET', $uri, $action);

        return $this;
    }

    /**
     * Add a route to the collection.
     *
     * @param  array|string  $method
     * @param  string  $uri
     * @param  mixed  $action
     * @return void
     */
    public function addRoute($method, $uri, $action)
    {
        $action = $this->parseAction($action);

        $uri = '/' . trim($uri, '/');

        if (is_array($method)) {
            foreach ($method as $verb) {
                $this->routes[$verb.$uri] = ['method' => $verb, 'uri' => $uri, 'action' => $action];
            }
        } else {
            $this->routes[$method.$uri] = ['method' => $method, 'uri' => $uri, 'action' => $action];
        }
    }

    /**
     * Parse the action into an array format.
     *
     * @param  mixed  $action
     * @return array
     */
    protected function parseAction($action)
    {
        if (is_string($action)) {
            return ['uses' => $action];
        } elseif (!is_array($action)) {
            return [$action];
        }
    }

    /**
     * {@inheritdoc}
     */
    public function handle(SymfonyRequest $request)
    {
        $response = $this->dispatch($request);

        return $response;
    }

    /**
     * Dispatch the incoming request.
     *
     * @param  SymfonyRequest|null  $request
     * @return Response
     */
    public function dispatch($request = null)
    {
        list($method, $pathInfo) = $this->parseIncomingRequest($request);
        
        return $this->sendThroughPipeline($this->middleware, function() use ($method, $pathInfo) {
            if (isset($this->routes[$method.$pathInfo])) {
                return $this->handleFoundRoute([true, $this->routes[$method.$pathInfo]['action'], []]);
            }
        });
    }

    /**
     * Handle a route found by the dispatcher.
     *
     * @param  array  $routeInfo
     * @return mixed
     */
    protected function handleFoundRoute($routeInfo)
    {
        $this->currentRoute = $routeInfo;

        // $this['request']->setRouteResolver(function () {
        //     return $this->currentRoute;
        // });

        return $this->prepareResponse(
            $this->callActionOnArrayBasedRoute($routeInfo)
        );
    }

    /**
     * Call the Closure on the array based route.
     *
     * @param  array  $routeInfo
     * @return mixed
     */
    protected function callActionOnArrayBasedRoute($routeInfo)
    {
        $action = $routeInfo[1];

        foreach ($action as $value) {
            if ($value instanceof Closure) {
                $closure = $value->bindTo(new RoutingClosure);
                break;
            }
        }

        return $this->prepareResponse($this->call($closure, $routeInfo[2]));
    }

    /**
     * Parse the incoming request and return the method and path info.
     *
     * @param  \Symfony\Component\HttpFoundation\Request|null  $request
     * @return array
     */
    protected function parseIncomingRequest($request)
    {
        if (!$request) {
            $request = Request::capture();
        }

        $this->instance(Request::class, $this->prepareRequest($request));

        return [$request->getMethod(), $request->getPathInfo()];
    }

    /**
     * Send the request through the pipeline with the given callback.
     *
     * @param  array  $middleware
     * @param  \Closure  $then
     * @return mixed
     */
    protected function sendThroughPipeline(array $middleware, Closure $then)
    {
        return $then();
    }

    /**
     * Prepare the response for sending.
     *
     * @param  mixed  $response
     * @return Response
     */
    public function prepareResponse($response)
    {
        // if ($response instanceof PsrResponseInterface) {
        //     $response = (new HttpFoundationFactory)->createResponse($response);
        // } elseif (!$response instanceof SymfonyResponse) {
        //     $response = new Response($response);
        // }

        return $response;
    }
}
