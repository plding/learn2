<?php
/**
 * Slim Framework (https://slimframework.com)
 *
 * @link      https://github.com/slimphp/Slim
 * @copyright Copyright (c) 2011-2017 Josh Lockhart
 * @license   https://github.com/slimphp/Slim/blob/3.x/LICENSE.md (MIT License)
 */
namespace Slim\Http;

use Closure;
use InvalidArgumentException;
use RuntimeException;
use Psr\Http\Message\UploadedFileInterface;
use Psr\Http\Message\ServerRequestInterface;
use Psr\Http\Message\UriInterface;
use Psr\Http\Message\StreamInterface;
use Slim\Collection;
use Slim\Exception\InvalidMethodException;
use Slim\Exception\MethodNotAllowedException;
use Slim\Interfaces\Http\HeadersInterface;

/**
 * Request
 *
 * This class represents an HTTP request. It manages
 * the request method, URI, headers, cookies, and body
 * according to the PSR-7 standard.
 *
 * @link https://github.com/php-fig/http-message/blob/master/src/MessageInterface.php
 * @link https://github.com/php-fig/http-message/blob/master/src/RequestInterface.php
 * @link https://github.com/php-fig/http-message/blob/master/src/ServerRequestInterface.php
 */
class Request extends Message implements ServerRequestInterface
{
    /**
     * The request method
     *
     * @var string
     */
    protected $method;

    /**
     * The original request method (ignoring override)
     *
     * @var string
     */
    protected $originalMethod;

    /**
     * The request URI object
     *
     * @var \Psr\Http\Message\UriInterface
     */
    protected $uri;

    /**
     * The request URI target (path + query string)
     *
     * @var string
     */
    protected $requestTarget;

    /**
     * The request query string params
     *
     * @var array
     */
    protected $queryParams;

    /**
     * The request cookies
     *
     * @var array
     */
    protected $cookies;

    /**
     * The server environment variables at the time the request was created.
     *
     * @var array
     */
    protected $serverParams;

    /**
     * The request attributes (route segment names and values)
     *
     * @var \Slim\Collection
     */
    protected $attributes;

    /**
     * The request body parsed (if possible) into a PHP array or object
     *
     * @var null|array|object
     */
    protected $bodyParsed = false;

    /**
     * List of request body parsers (e.g., url-encoded, JSON, XML, multipart)
     *
     * @var callable[]
     */
    protected $bodyParsers = [];

    /**
     * List of uploaded files
     *
     * @var UploadedFileInterface[]
     */
    protected $uploadedFiles;

    /**
     * Valid request methods
     *
     * @var string[]
     */
    protected $validMethods = [
        'CONNECT' => 1,
        'DELETE' => 1,
        'GET' => 1,
        'HEAD' => 1,
        'OPTIONS' => 1,
        'PATCH' => 1,
        'POST' => 1,
        'PUT' => 1,
        'TRACE' => 1,
    ];

    
}
