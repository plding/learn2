<?php

namespace Lumen\Concerns;

use Closure;
use Symfony\Component\HttpFoundation\Request as SymfonyRequest;

trait RoutesRequests
{
    /**
     * All of the routes waiting to be registered.
     *
     * @var array
     */
    private $routes = [];

    /**
     * Register a route with the application.
     *
     * @param  string $uri
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
     * @param  array|string $method
     * @param  string       $uri
     * @param  mixed        $action
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
        return [$action];
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
    public function dispatch($request)
    {
        list($method, $pathInfo) = $this->parseIncomingRequest($request);

        if (isset($this->routes[$method.$pathInfo])) {
            return $this->handleFoundRoute([true, $this->routes[$method.$pathInfo]['action'], []]);
        }
    }

    /**
     * Parse the incoming request and return the method and path info.
     *
     * @param  \Symfony\Component\HttpFoundation\Request|null  $request
     * @return array
     */
    protected function parseIncomingRequest($request)
    {
        return [$request->getMethod(), $request->getPathInfo()];
    }

    /**
     * Handle a route found by the dispatcher.
     *
     * @param  array  $routeInfo
     * @return mixed
     */
    protected function handleFoundRoute($routeInfo)
    {
        return $this->callActionOnArrayBasedRoute($routeInfo);
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
                $closure = $value->bindTo($this);
                break;
            }
        }

        return $this->call($closure, $routeInfo[2]);
    }
}
