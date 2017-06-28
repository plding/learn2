<?php

namespace Slim;

class Route
{
    /**
     * @var string The route pattern (e.g. "/books/:id")
     */
    protected $pattern;

    /**
     * @var mixed The route callable
     */
    protected $callable;

    /**
     * @var array Conditions for this route's URL parameters
     */
    protected $conditions = array();

    /**
     * @var array Default conditions applied to all route instances
     */
    protected static $defaultConditions = array();

    /**
     * @var array Key-value array of URL parameters
     */
    protected $params = array();

    /**
     * @var array value array of URL parameter names
     */
    protected $paramNames = array();

    /**
     * @var array key array of URL parameter names with + at the end
     */
    protected $paramNamesPath = array();

    /**
     * @var bool Whether or not this route should be matched in a case-sensitive manner
     */
    protected $caseSensitive;

    /**
     * Constructor
     * @param string $pattern The URL pattern (e.g. "/books/:id")
     * @param mixed $callable Anything that returns TRUE for is_callable()
     * @param bool $caseSensitive Whether or not this route should be matched in a case-sensitive manner
     */
    public function __construct($pattern, $callable, $caseSensitive = true)
    {
        $this->setPattern($pattern);
        $this->setCallable($callable);
        $this->setConditions(self::getDefaultConditions());
        $this->caseSensitive = $caseSensitive;
    }

    /**
     * Set default route conditions for all instances
     * @param  array $defaultConditions
     */
    public static function setDefaultConditions(array $defaultConditions)
    {
        self::$defaultConditions = $defaultConditions;
    }

    /**
     * Get default route conditions for all instances
     * @return array
     */
    public static function getDefaultConditions()
    {
        return self::$defaultConditions;
    }

    /**
     * Get route pattern
     * @return string
     */
    public function getPattern()
    {
        return $this->pattern;
    }

    /**
     * Set route pattern
     * @param  string $pattern
     */
    public function setPattern($pattern)
    {
        $this->pattern = $pattern;
    }

    /**
     * Get route callable
     * @return mixed
     */
    public function getCallable()
    {
        return $this->callable;
    }

    /**
     * Set route callable
     * @param  mixed $callable
     * @throws \InvalidArgumentException If argument is not callable
     */
    public function setCallable($callable)
    {
        // $matches = array();
        // if (is_string($callable))

        $this->callable = $callable;
    }

    /**
     * Get route conditions
     * @return array
     */
    public function getConditions()
    {
        return $this->conditions;
    }

    /**
     * Set route conditions
     * @param  array $conditions
     */
    public function setConditions(array $conditions)
    {
        $this->conditions = $conditions;
    }

    /**
     * Get route parameters
     * @return array
     */
    public function getParams()
    {
        return $this->params;
    }

    /**
     * Set route parameters
     * @param  array $params
     */
    public function setParams($params)
    {
        $this->params = $params;
    }

    /**
     * Matches URI?
     *
     * Parse this route's pattern, and then compare it to an HTTP resource URI
     * This method was modeled after the techniques demonstrated by Dan Sosedoff at:
     *
     * http://blog.sosedoff.com/2009/09/20/rails-like-php-url-router/
     *
     * @param  string $resourceUri A Request URI
     * @return bool
     */
    public function matches($resourceUri)
    {
        // Convert URL params into regex patterns, construct a regex for this route, init params
        $patternAsRegex = preg_replace_callback(
            '#:([\w]+)\+?#',
            array($this, 'matchesCallback'),
            str_replace(')', ')?', (string) $this->pattern)
        );

        if (substr($this->pattern, -1) == '/') {
            $patternAsRegex .= '?';
        }

        $regex = '#^' . $patternAsRegex . '$#';

        if ($this->caseSensitive == false) {
            $regex .= 'i';
        }

        // Cache URL params' names and values if this route matches the current HTTP request
        if (!preg_match($regex, $resourceUri, $paramValues)) {
            return false;
        }
        foreach ($this->paramNames as $name) {
            if (isset($paramValues[$name])) {
                if (isset($this->paramNamesPath[$name])) {
                    $this->params[$name] = explode('/', urldecode($paramValues[$name]));
                } else {
                    $this->params[$name] = urldecode($paramValues[$name]);
                }
            }
        }
        
        return true;
    }

    /**
     * Convert a URL parameter (e.g. ":id", ":id+") into a regular expression
     * @param  array $m URL parameters
     * @return string       Regular expression for URL parameter
     */
    protected function matchesCallback($m)
    {
        $this->paramNames[] = $m[1];
        if (isset($this->conditions[$m[1]])) {
            return '(?P<' . $m[1] . '>' . $this->conditions[$m[1]] . ')';
        }
        if (substr($m[0], -1) == '+') {
            $this->paramNames[$m[1]] = 1;

            return '(?P<' . $m[1] . '>.+)';
        }

        return '(?P<' . $m[1] . '>[^/]+)';
    }

    /**
     * Dispatch route
     *
     * This method invokes the route object's callable. If middleware is
     * registered for the route, each callable middleware is invoked in
     * the order specified.
     *
     * @return bool
     */
    public function dispatch()
    {
        $return = call_user_func_array($this->getCallable(), array_values($this->getParams()));
        return ($return === false) ? false : true;
    }
}
