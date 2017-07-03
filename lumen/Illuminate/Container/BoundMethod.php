<?php

namespace Illuminate\Container;

class BoundMethod
{
    /**
     * Call the given Closure / class@method and inject its dependencies.
     *
     * @param  \Illuminate\Container\Container  $container
     * @param  callable|string                  $callback
     * @param  array                            $parameters
     * @param  string|null                      $defaultMethod
     * @return mixed
     */
    public static function call($container, $callback, array $parameters = [], $defaultMethod = null)
    {
        return call_user_func_array($callback, $parameters);
    }
}
