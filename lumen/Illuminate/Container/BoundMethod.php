<?php

namespace Illuminate\Container;

use Closure;

class BoundMethod
{
    /**
     * Call the given Closure / class@method and inject its dependencies.
     *
     * @param  \Illuminate\Container\Container  $container
     * @param  callable|string  $callback
     * @param  array  $parameters
     * @param  string|null  $defaultMethod
     * @return mixed
     */
    public static function call($container, $callback, array $parameters = [], $defaultMethod = null)
    {
        return static::callBoundMethod($container, $callback, function () use ($container, $callback, $parameters) {
            return call_user_func_array(
                $callback, []
            );
        });
    }

    /**
     * Call a method that has been bound to the container.
     *
     * @param  \Illuminate\Container\Container  $container
     * @param  callable  $callback
     * @param  mixed  $default
     * @return mixed
     */
    protected static function callBoundMethod($container, $callback, $default)
    {
        if (!is_array($callback)) {
            return $default instanceof Closure ? $default() : $default;
        }
    }
}
