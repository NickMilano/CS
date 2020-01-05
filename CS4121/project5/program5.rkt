(define (last n L)
  (local ((define(last-help n L i c)
      (cond
        [(null? L)  i]
        [(eq? (first L) n)
          (last-help n (rest L) c (add1 c))]
        [else (last-help n (rest L) i (add1 c))])))
      (last-help n L 0 0))
    )

(define (wrap M)
  (cond
    [(null? M) M]
    [else (cons (cons (first M) '()) (wrap (rest M)))]))

(define (count-parens-all M)
  (local ((define(count-help M n)
    (cond
      [(null? M) (add1 (add1 n))]
      [(list? (first M)) (count-help (rest M) (add1 (add1 n)))]
      [else (count-help (rest M) n)])))
    (count-help M 0))
  )

  (define (insert-right-all new old M)
    (cond
    [(null? M) '()]
    [(pair? (first M)) (cons (insert-right-all new old (car M)) (insert-right-all new old (cdr M)))]
    [(eq? (car M) old) (append (cons old (cons new null))  (insert-right-all new old (cdr M)))]
    [else (cons (car M)(insert-right-all new old (cdr M)))]))


  (define (invert M)
  (cond
    [(null? M) M]
    [else (cons (reverse (first M)) (invert (rest M)))]))

  (define (filter-out pred L)
  (cond
    [(null? L) L]
    [(pred (first L)) (filter-out pred (rest L))]
    [else (cons (first L) (filter-out pred (rest L)))]))

  (define (summatrices M1 M2)
  (cond
    [(null? M1) M2]
    [(null? M2) M1]
    [(list? (first M1)) (cons (summatrices (first M1) (first M2)) (summatrices (rest M1) (rest M2)))]
    [(list? (first M2)) (summatrices (first M1) (first M2))]
    [else (cons (+ (first M1) (first M2)) (summatrices (rest M1) (rest M2)))]))

  (define (swapper a1 a2 M)
  (cond
    [(null? M) '()]
    [(eq? (first M) a1) (cons a2 (rest M))]
    [(list? (first M)) (cons (swapper a1 a2 (first M)) (swapper a1 a2 (rest M)))]
    [else (cons (first M) (swapper a1 a2 (rest M)))]))

  (define (flatten M)
  (cond
    [(null? M) '()]
    [(not(pair? M)) (list M)]
    [else(append (flatten (first M)) (flatten (rest M)))] ))

    (define (rember* a M)
    (cond
    [(null? M) '()]
    [(not (pair? (first M))) (if (eq? a (first M))
    (rember* a (rest M))
    (cons (first M) (rember* a (rest M))))]
    [else (cons (rember* a (first M))
    (rember* a (rest M)))]))


  (define (abstractrd f g h)
    (local ((define (helper a M)
      (cond[(null? M) (f a M)]
      [(not(pair? (first M))) (g a M)]
      [else (h a M)])))
      helper ))

    (define remember*1
      (abstractrd (lambda (a M) '()) (lambda(a M) (if (eq? a (first M)) (remember*1 a (rest M))
                                                    (cons(first M) (remember*1 a (rest M)))))
                  (lambda (a M) (cons (remember*1 a (first M)) (remember*1 a (rest M))))))
    (define depth1
      (abstractrd (lambda (a M) 1) (lambda (a M) (depth1 (rest M))) (lambda (a M) (max (add1 (depth1 (first M))) (depth1 (rest M))))))
