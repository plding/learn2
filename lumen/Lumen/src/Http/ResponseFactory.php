<?php

namespace Lumen\Http;

use Illuminate\Http\Response;
use Illuminate\Http\JsonResponse;
// use Illuminate\Contracts\Support\Arrayable;

class ResponseFactory
{
    /**
     * Return a new response from the application.
     *
     * @param  string  $content
     * @param  int     $status
     * @param  array   $headers
     * @return \Illuminate\Http\Response
     */
    public function make($content = '', $status = 200, array $headers = [])
    {
        return new Response($content, $status, $headers);
    }

    /**
     * Return a new JSON response from the application.
     *
     * @param  string|array  $data
     * @param  int    $status
     * @param  array  $headers
     * @param  int    $options
     * @return \Illuminate\Http\JsonResponse;
     */
    public function json($data = [], $status = 200, array $headers = [], $options = 0)
    {
        // if ($data instanceof Arrayable) {
        //     $data = $data->toArray();
        // }

        return new JsonResponse($data, $status, $headers, $options);
    }
}
